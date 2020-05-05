#version 400 core


out vec4 outColor;

uniform mat4 camera;
uniform vec2 resolution;

uniform float shadowSharpness;

/// COMPILATION FLAGS
//#pragma optionNV (unroll all)

/// OPTIONS
#define WITH_SHADOWS
#define WITH_AMBIENT_OCCLUSION
//#define WITH_FOG
//#define WITH_GLOW

#define SAMPLES_PER_PIXEL_SIDE 1


/// Definitions
#define AMBIENT_OCCLUSION_STRENGTH 0.008
#define AMBIENT_OCCLUSION_COLOR_DELTA vec4(vec3(0.2), 1)
#define FOCAL_DIST 1.73205080757
#define GLOW_COLOR vec4(0.7, 0.2, 0, 1)
#define GLOW_INTENSITY 0.07
#define MAX_RAY_STEPS 500
#define HIT_DISTANCE 1e-5
#define FAR_PLANE 50.0


#define RGB_BYTES(r, g, b) vec4(r, g, b, 1) / vec4(255, 255, 255, 1);

/// Fractal Params
#define Iterations 20
#define Bailout 2

#define PAX_POW_8(b) b * b * b * b * b * b * b * b
#define PAX_POW_7(b) b * b * b * b * b * b * b
#define PAX_POW_2(b) b * b

/*
#define MANDELBULB_POWER 2
#define MANDELBULB_POWER_FUN(b) PAX_POW_2(b)
#define MANDELBULB_POWER_FUN_DERIV(b) b
/*/
#define MANDELBULB_POWER 8
#define MANDELBULB_POWER_FUN(b) PAX_POW_8(b)
#define MANDELBULB_POWER_FUN_DERIV(b) PAX_POW_7(b)
//*/

vec4 SkyColor = RGB_BYTES(0, 204, 255)

struct Ray {
    vec3 pos;
    vec3 dir;
};

struct Trace {
    Ray ray;
    vec3 hitpos;
    float steps;
    float travelledDistance;
    float lastDistanceEstimate;
    int fractalIterations;
    //float normalisedMinDistance;
};

/// Lights
#define NUM_DIRECTIONAL_LIGHTS 1
struct DirectionalLight {
    vec3 direction;
    vec4 color;
};
DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];


/// Distance Estimator Operations

float op_union(in float de1, in float de2) {
    return min(de1, de2);
}

float op_intersection(in float de1, in float de2) {
    return max(de1, de2);
}

float op_substract(in float de1, in float de2) {
    return op_intersection(de1, -de2);
}

// folds

void fold_mod(inout vec3 pos, in float spaceLength) {
    pos = mod(pos, spaceLength) - vec3(0.5 * spaceLength);
}

/// Distance Estimators

float de_sphere(in vec3 pos, vec3 spherepos, float radius) {
    return length(pos - spherepos) - radius;
}

float de_cube(vec3 pos, vec3 cubepos, float halfSideLength) {
    return length(max(abs(pos - cubepos) - halfSideLength, 0));
}

float de_tetrahedron(vec3 p, vec3 tetrahedronpos, float r) {
    p -= tetrahedronpos;
    float md = max(max(-p.x - p.y - p.z, p.x + p.y - p.z),
    max(-p.x + p.y + p.z, p.x - p.y + p.z));
    return (md - r) / sqrt(3.0);
}

float de_mandelbulb(vec3 pos, out int fractalIterations) {
    vec3 z = pos;
    float dr = 1.0;
    float r = 0.0;
    int i;
    for (i = 0; i < Iterations ; i++) {
        r = length(z);
        if (r>Bailout) break;

        // convert to polar coordinates
        float theta = acos(z.z/r);
        float phi = atan(z.y,z.x);
        dr =  MANDELBULB_POWER_FUN_DERIV(r)*MANDELBULB_POWER*dr + 1.0;

        // scale and rotate the point
        float zr = MANDELBULB_POWER_FUN(r);
        theta = theta*MANDELBULB_POWER;
        phi = phi*MANDELBULB_POWER;

        // convert back to cartesian coordinates
        z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
        z+=pos;
    }
    fractalIterations = i;
    return 0.5*log(r)*r/dr;
}

float DE(in vec3 pos, out int fractalIterations) {
    //fold_mod(pos, 3);
    /*
    return op_union(
            op_union(
                de_sphere(pos, vec3(0, 0, 0), 0.3)
                , de_tetrahedron(pos, vec3(0, 1, 0), 0.2))
            ,op_substract(
                de_cube(pos, vec3(1, 0, 0), 0.3),
                de_sphere(pos, vec3(1, 0, 0), 0.4)
        ))
    ;/*/
    float scale = 0.5;
    return de_mandelbulb(pos/scale, fractalIterations)*scale;//*/
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 getDiffuseColor(in Trace trace, in vec3 normal) {
    float h = float(trace.fractalIterations) / float(Iterations);
    float s = 0.7 * float(Iterations - trace.fractalIterations) / float(Iterations);
    float v = 0.9;
    return hsv2rgb(vec3(h, s, v));
    return normal;
}

/// Shading

vec3 calculateNormal(in Trace trace) {
    const float epsilon = 0.5*HIT_DISTANCE;
//*
    const vec2 k = vec2(1, -1);
    int discardedFractalIterations;
    return normalize(
          k.xyy * DE(trace.hitpos + k.xyy*epsilon, discardedFractalIterations)
        + k.yyx * DE(trace.hitpos + k.yyx*epsilon, discardedFractalIterations)
        + k.yxy * DE(trace.hitpos + k.yxy*epsilon, discardedFractalIterations)
        + k.xxx * DE(trace.hitpos + k.xxx*epsilon, discardedFractalIterations)
    );
/*/
    const vec2 epsilonv = vec2(epsilon, 0);
    return normalize(vec3(
        DE(trace.hitpos + epsilonv.xyy) - DE(trace.hitpos - epsilonv.xyy),
        DE(trace.hitpos + epsilonv.yxy) - DE(trace.hitpos - epsilonv.yxy),
        DE(trace.hitpos + epsilonv.yyx) - DE(trace.hitpos - epsilonv.yyx)
    ));
//*/
}


/// Ray Tracing

Trace march(in Ray ray) {
    float steps;
    float travelledDistance = 0;
    float distance;
    float normalisedMinDistance = 1;
    int fractalIterations = 0;

    vec3 position = ray.pos;    
    for (steps = 0; steps < MAX_RAY_STEPS; ++steps) {
        distance = DE(position, fractalIterations);

        if (distance < HIT_DISTANCE) {
            steps += distance / HIT_DISTANCE;
            break;
        } else if (travelledDistance > FAR_PLANE) {
            break;
        }

        position += distance * ray.dir;
        travelledDistance += distance;
        //normalisedMinDistance = min(normalisedMinDistance, distance / travelledDistance);
    }

    travelledDistance = min(travelledDistance, FAR_PLANE);
    return Trace(ray, position, steps, travelledDistance, distance, fractalIterations);
}

vec4 getColor(inout Trace trace) {
    vec4 shadyColor;
    if (trace.lastDistanceEstimate < HIT_DISTANCE) {
        vec3 normal = calculateNormal(trace);
        trace.hitpos = trace.hitpos - normal * trace.lastDistanceEstimate;
        shadyColor = vec4(getDiffuseColor(trace, normal), 1);

#ifdef WITH_SHADOWS
        for (int i = 0; i < NUM_DIRECTIONAL_LIGHTS; ++i) {
            Ray shadowRay = Ray(trace.hitpos, -directionalLights[i].direction);

            // We would not be able to escape a position on the surface of the scene without this little step,
            // because we would always obtain a hit.
            shadowRay.pos += normal * 100 * HIT_DISTANCE;

            Trace shadowTrace = march(shadowRay);
            float weight = float(shadowTrace.lastDistanceEstimate > HIT_DISTANCE);

            // Lambert shading
            weight *= max(0, dot(normal, shadowRay.dir));

            shadyColor += weight * directionalLights[i].color;
        }
#endif

#ifdef WITH_AMBIENT_OCCLUSION
        shadyColor = mix(AMBIENT_OCCLUSION_COLOR_DELTA, shadyColor, 1.0 / (1.0 + trace.steps * AMBIENT_OCCLUSION_STRENGTH));
#endif


    /// Show amount of steps needed
    /*
    float gradient = trace.steps / 20;
    return vec4(gradient, gradient, gradient, 1);
    //*/

    // Mix with background
    } else {
        shadyColor = SkyColor;

#ifdef WITH_GLOW
        float glowFactor = GLOW_INTENSITY * trace.steps;
        glowFactor = glowFactor / (glowFactor + 1);
        shadyColor += glowFactor * GLOW_COLOR;
#endif
    }

#ifndef WITH_FOG
    float fogFactor = trace.travelledDistance / (trace.travelledDistance + 1);
    fogFactor = pow(fogFactor, 3);
    shadyColor = mix(shadyColor, SkyColor, fogFactor);
#endif

    return shadyColor;
}

void main(void) {
    // TODO: Move this to uniform buffer:
    directionalLights[0] = DirectionalLight(normalize(vec3(0.2, -1, -0.2)), vec4(0.5, 0.5, 0.5, 1));

    float aspectRatio = resolution.y / resolution.x;
    vec2 uv = gl_FragCoord.xy / resolution;
    vec2 pixelSize = vec2(2.0) / resolution;
    vec2 screen = 2*uv - 1;
    screen.y *= aspectRatio;

    vec4 color = vec4(0);
    for (int samples_x = 1; samples_x < SAMPLES_PER_PIXEL_SIDE + 1; ++samples_x) {
        for (int samples_y = 1; samples_y < SAMPLES_PER_PIXEL_SIDE + 1; ++samples_y) {
            float xOffset = pixelSize.x * ((float(samples_x) / float(SAMPLES_PER_PIXEL_SIDE + 2)) - 0.5);
            float yOffset = pixelSize.y * ((float(samples_y) / float(SAMPLES_PER_PIXEL_SIDE + 2)) - 0.5);

            Ray ray;
            ray.dir = normalize(mat3(camera) * vec3(screen.x + xOffset, screen.y + yOffset, -FOCAL_DIST));
            ray.pos = vec3(camera[3]);

            Trace trace = march(ray);
            color += getColor(trace);
        }
    }

    outColor = color / (SAMPLES_PER_PIXEL_SIDE * SAMPLES_PER_PIXEL_SIDE);
}