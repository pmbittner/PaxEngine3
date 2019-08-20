#version 400 core


out vec4 outColor;

uniform mat4 camera;
uniform vec2 resolution;

/// OPTIONS
#define WITH_HARD_SHADOWS
#define WITH_AMBIENT_OCCLUSION


/// Definitions
#define FOCAL_DIST 1.73205080757
#define MAX_RAY_STEPS 1000
#define HIT_DISTANCE 1e-5
#define FAR_PLANE 50.0
#define SHADOW_SHARPNESS 5.0

#define SAMPLES_PER_PIXEL_SIDE 2

#define RGB_BYTES(r, g, b) vec4(r, g, b, 1) / vec4(255, 255, 255, 1);

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
    float normalisedMinDistance;
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

float SDF(in vec3 pos) {
    //fold_mod(pos, 3);
    return op_union(
            op_union(
                de_sphere(pos, vec3(0, 0, 0), 0.3)
                , de_tetrahedron(pos, vec3(0, 1, 0), 0.2))
            ,op_substract(
                de_cube(pos, vec3(1, 0, 0), 0.3),
                de_sphere(pos, vec3(1, 0, 0), 0.4)
        ))
    ;
}


/// Shading

vec3 calculateNormal(in Trace trace) {
    const vec2 k = vec2(1, -1);
    const float epsilon = 0.5 * HIT_DISTANCE;
    return normalize(
          k.xyy * SDF(trace.hitpos + k.xyy*epsilon)
        + k.yyx * SDF(trace.hitpos + k.yyx*epsilon)
        + k.yxy * SDF(trace.hitpos + k.yxy*epsilon)
        + k.xxx * SDF(trace.hitpos + k.xxx*epsilon)
    );
}


/// Ray Tracing

Trace march(in Ray ray) {
    float steps;
    float travelledDistance = 0;
    float distance;
    float normalisedMinDistance = 1.0;

    vec3 position = ray.pos;    
    for (steps = 0; steps < MAX_RAY_STEPS; ++steps) {
        distance = SDF(position);

        if (distance < HIT_DISTANCE) {
            if (0 <= distance) {
                steps += distance / HIT_DISTANCE;
                break;
            } else { // distance < 0
                // We are inside the scene.
                //steps -= distance / HIT_DISTANCE;
            }
        } else if (travelledDistance > FAR_PLANE) {
            break;
        }

        position += distance * ray.dir;
        travelledDistance += distance;
        normalisedMinDistance = min(normalisedMinDistance, SHADOW_SHARPNESS * distance / travelledDistance);
    }

    return Trace(ray, position, steps, travelledDistance, distance, normalisedMinDistance);
}

vec4 getColor(in Trace trace) {
    if (trace.lastDistanceEstimate < HIT_DISTANCE) {
        const vec4 diffuseColor = vec4(0.7, 0.5, 0, 1);
        vec3 normal = calculateNormal(trace);
        vec3 surfacePoint = trace.hitpos - normal * trace.lastDistanceEstimate;
        vec4 shadyColor = max(dot(normal, -trace.ray.dir), 0) * diffuseColor;
        
        //*
#ifdef WITH_HARD_SHADOWS
        for (int i = 0; i < NUM_DIRECTIONAL_LIGHTS; ++i) {
            Ray shadowRay = Ray(surfacePoint, -directionalLights[i].direction);
            
            // We would not be able to escape a position on the surface of the scene without this little step,
            // because we would always obtain a hit.
            shadowRay.pos += normal * 100 * HIT_DISTANCE;
    
            Trace shadowTrace = march(shadowRay);
            
            if (shadowTrace.lastDistanceEstimate > HIT_DISTANCE) {
                // not in shadow
                //shadyColor += shadowTrace.normalisedMinDistance * directionalLights[i].color;
                shadyColor += directionalLights[i].color;
                //shadyColor = vec4(1, 0, 0, 1);
            } else {
                //shadyColor = vec4(0, 0, 1, 1);
            }
        }
#endif
        //*/
        
#ifdef WITH_AMBIENT_OCCLUSION
        float AMBIENT_OCCLUSION_STRENGTH = 0.008;
        vec4 AMBIENT_OCCLUSION_COLOR_DELTA = vec4(vec3(0.2), 1);
        shadyColor = mix(AMBIENT_OCCLUSION_COLOR_DELTA, shadyColor, 1.0 / (1.0 + trace.steps * AMBIENT_OCCLUSION_STRENGTH));
#endif
        
        return shadyColor;
        
        /// Show amount of steps needed
        /*
        float gradient = trace.steps / 20;
        return vec4(gradient, gradient, gradient, 1);
        //*/
    } else {
        return SkyColor;
    }
}

void main(void) {
    // TODO: Move this to uniform buffer:
    directionalLights[0] = DirectionalLight(normalize(vec3(0.2, -1, -0.2)), vec4(0.5, 0.5, 0.5, 1));

    vec2 screen_pos = gl_FragCoord.xy / resolution;
    vec2 pixelSize = vec2(2.0) / resolution;
    vec2 uv = 2*screen_pos - 1;

    vec4 color = vec4(0);
    for (int samples_x = 0; samples_x < SAMPLES_PER_PIXEL_SIDE; ++samples_x) {
        for (int samples_y = 0; samples_y < SAMPLES_PER_PIXEL_SIDE; ++samples_y) {
            float xOffset = pixelSize.x * ((float(samples_x) / float(SAMPLES_PER_PIXEL_SIDE - 1)) - 0.5);
            float yOffset = pixelSize.y * ((float(samples_y) / float(SAMPLES_PER_PIXEL_SIDE - 1)) - 0.5);

            Ray ray;
            ray.dir = mat3(camera) * normalize(vec3(uv.x + xOffset, uv.y + yOffset, -FOCAL_DIST));
            ray.pos = vec3(camera[3]);

            Trace trace = march(ray);
            color += getColor(trace);
        }
    }

    outColor = color / (SAMPLES_PER_PIXEL_SIDE * SAMPLES_PER_PIXEL_SIDE);
}