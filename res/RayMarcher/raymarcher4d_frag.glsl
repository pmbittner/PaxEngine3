#version 400 core


out vec4 outColor;

uniform mat4 camera;
uniform vec2 resolution;
uniform float shadowSharpness;
uniform float gameTimeDelta;
uniform float gameTime;

/// OPTIONS
//#define WITH_SHADOWS
//#define WITH_AMBIENT_OCCLUSION
//#define WITH_FOG
#define WITH_GLOW

#define SAMPLES_PER_PIXEL_SIDE 2


/// Definitions
#define RAY_4D_PLANE_DIR_W 0
#define RAY_4D_CAM_POS_W 0

#define AMBIENT_OCCLUSION_STRENGTH 0.008
#define AMBIENT_OCCLUSION_COLOR_DELTA vec4(vec3(0.2), 1)
#define FOCAL_DIST 1.73205080757
#define GLOW_COLOR vec4(0.7, 0.2, 0, 1)
#define GLOW_INTENSITY 0.17
#define MAX_RAY_STEPS 500
#define HIT_DISTANCE 1e-5
#define FAR_PLANE 50.0


#define RGB_BYTES(r, g, b) (vec4(r, g, b, 1) / vec4(255, 255, 255, 1))

vec4 SkyColor = RGB_BYTES(0, 204, 255);

struct Ray {
    vec4 pos;
    vec4 dir;
};

struct Trace {
    Ray ray;
    vec4 hitpos;
    float steps;
    float travelledDistance;
    float lastDistanceEstimate;
    //float normalisedMinDistance;
};

/// Lights
#define NUM_DIRECTIONAL_LIGHTS 1
struct DirectionalLight {
    vec3 direction;
    vec4 color;
};
DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];

/// Math Util

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(
    oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
    oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
    oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
    0.0,                                0.0,                                0.0,                                1.0);
}

mat4 rotmat_y(float angle) {
    mat4 R = mat4(1);
    float s = sin(angle);
    float c = cos(angle);

    R[0][0] = c;
    R[0][2] = -s;

    R[2][0] = s;
    R[2][2] = c;

    return R;
}

mat4 rotmat_xw(float angle) {
    mat4 R = mat4(1);
    float s = sin(angle);
    float c = cos(angle);

    R[0][0] = c;
    R[0][3] = -s;

    R[3][0] = s;
    R[3][3] = c;

    return R;
}

mat4 rotmat_yw(float angle) {
    mat4 R = mat4(1);
    float s = sin(angle);
    float c = cos(angle);

    R[1][1] = c;
    R[1][3] = s;

    R[3][1] = -s;
    R[3][3] = c;

    return R;
}

mat4 rotmat_zw(float angle) {
    mat4 R = mat4(1);
    float s = sin(angle);
    float c = cos(angle);

    R[2][2] = c;
    R[2][3] = s;

    R[3][2] = -s;
    R[3][3] = c;

    return R;
}

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

/// Distance Estimators

float de_sphere4(in vec4 pos, vec4 spherepos, float radius) {
    return length(pos - spherepos) - radius;
}

float de_cube4(vec4 pos, vec4 cubepos, float halfSideLength) {
    return length(max(abs(pos - cubepos) - halfSideLength, 0));
}

/// Scene

float DE(in vec4 pos) {
    //mat4 R = rotationMatrix(vec3(0, 1, 0), 0.1 * gameTime);
    //mat4 R = rotmat_yw(0.4 * gameTime);
    //R = R * rotmat_zw(0.3 * gameTime);
    //R = R * rotmat_xw(0.25423 * gameTime);
    //R = R * rotmat_y(0.1 * gameTime);

    //pos = R * pos;

    return de_sphere4(pos, vec4(0, 0, 0, sin(gameTime)), 1);
    //return de_cube4(pos, vec4(0, 0, 0, 0), 0.3);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 getDiffuseColor(in Trace trace, in vec3 normal) {
    return normal;
}

/// Shading

vec3 calculateNormal(in Trace trace) {
    const float epsilon = 0.5*HIT_DISTANCE;
    const vec2 k = vec2(1, -1);
    return normalize(
          k.xyy * DE(trace.hitpos + vec4(k.xyy*epsilon, 0)) // 0 = no 4d lighting
        + k.yyx * DE(trace.hitpos + vec4(k.yyx*epsilon, 0))
        + k.yxy * DE(trace.hitpos + vec4(k.yxy*epsilon, 0))
        + k.xxx * DE(trace.hitpos + vec4(k.xxx*epsilon, 0))
    );
}


/// Ray Tracing

Trace march(in Ray ray) {
    float steps;
    float travelledDistance = 0;
    float distance;
    float normalisedMinDistance = 1;

    vec4 position = ray.pos;    
    for (steps = 0; steps < MAX_RAY_STEPS; ++steps) {
        distance = DE(position);

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
    return Trace(ray, position, steps, travelledDistance, distance);
}

vec4 getColor(inout Trace trace) {
    vec4 shadyColor;
    if (trace.lastDistanceEstimate < HIT_DISTANCE) {
        vec3 normal = calculateNormal(trace);
        trace.hitpos = vec4(trace.hitpos.xyz - normal * trace.lastDistanceEstimate, trace.hitpos.w);
        shadyColor = vec4(getDiffuseColor(trace, normal), 1);

#ifdef WITH_SHADOWS
        for (int i = 0; i < NUM_DIRECTIONAL_LIGHTS; ++i) {
            Ray shadowRay = Ray(trace.hitpos, vec4(-directionalLights[i].direction, 0));

            // We would not be able to escape a position on the surface of the scene without this little step,
            // because we would always obtain a hit.
            shadowRay.pos += vec4(normal * 100 * HIT_DISTANCE, 0);

            Trace shadowTrace = march(shadowRay);
            float weight = float(shadowTrace.lastDistanceEstimate > HIT_DISTANCE);

            // Lambert shading
            weight *= max(0, dot(normal, shadowRay.dir.xyz));

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
			vec3 raydir_3d = normalize(mat3(camera) * vec3(screen.x + xOffset, screen.y + yOffset, -FOCAL_DIST));
            ray.dir = vec4(raydir_3d, RAY_4D_PLANE_DIR_W);
            ray.pos = vec4(camera[3].xyz, RAY_4D_CAM_POS_W);

            Trace trace = march(ray);
            color += getColor(trace);
        }
    }

    outColor = color / (SAMPLES_PER_PIXEL_SIDE * SAMPLES_PER_PIXEL_SIDE);
}