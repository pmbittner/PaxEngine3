#version 400 core


out vec4 outColor;

uniform mat4 camera;
uniform vec2 resolution;

/// Definitions
#define FOCAL_DIST 1.73205080757
#define MAX_RAY_STEPS 1000
#define HIT_DISTANCE 1e-5
#define FAR_PLANE 50.0

vec4 SkyColor = vec4(0, 204, 255, 1) / vec4(255, 255, 255, 1);

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
};


/// Distance Estimators

float de_sphere_field(in vec3 pos, vec3 spherepos, float radius) {
    pos = mod(pos - spherepos, 1.0) - vec3(0.5);
    return length(pos) - radius;
}

float de_sphere(in vec3 pos, vec3 spherepos, float radius) {
    return length(pos - spherepos) - radius;
}

float de_cube(vec3 pos, vec3 cubepos, float sideLength) {
    return length(max(abs(pos - cubepos) - sideLength, 0));
}

float DistanceEstimator(in vec3 pos) {
    return
    //min(
    de_sphere_field(pos, vec3( 0, 0, 0), 0.3)
    //min(
    //    de_sphere(pos, vec3(-1, 0, 0), 0.3),
    //    de_cube(pos, vec3(1, 0, 0), 0.2)
    //))
    ;
}


/// Shading

vec3 calculateNormal(in Trace trace) {
    const vec2 k = vec2(1, -1);
    const float dx = HIT_DISTANCE;
    return normalize(
          k.xyy * DistanceEstimator(trace.hitpos + k.xyy*dx)
        + k.yyx * DistanceEstimator(trace.hitpos + k.yyx*dx)
        + k.yxy * DistanceEstimator(trace.hitpos + k.yxy*dx)
        + k.xxx * DistanceEstimator(trace.hitpos + k.xxx*dx)
    );
}


/// Ray Tracing

Trace march(in Ray ray) {
    float steps;
    float travelledDistance = 0;
    float distance;

    vec3 position = ray.pos;
    for (steps = 0; steps < MAX_RAY_STEPS; ++steps) {
        distance = DistanceEstimator(position);

        if (distance < HIT_DISTANCE) {
            steps += distance / HIT_DISTANCE;
            break;
        } else if (travelledDistance > FAR_PLANE) {
            break;
        }

        position += distance * ray.dir;
        travelledDistance += distance;
    }

    return Trace(ray, position, steps, travelledDistance, distance);
}

vec4 getColor(in Trace trace) {
    if (trace.lastDistanceEstimate < HIT_DISTANCE) {
        vec3 normal = calculateNormal(trace);
        const vec4 diffuseColor = vec4(1, 1, 0, 1);
        return max(dot(normal, -trace.ray.dir), 0) * diffuseColor;
        //return diffuseColor;
    } else {
        return SkyColor;
    }
}

void main(void) {
    vec2 screen_pos = gl_FragCoord.xy / resolution.xy;
    vec2 uv = 2*screen_pos - 1;

    //Convert screen coordinate to 3d ray
    Ray ray;
    ray.dir = vec3(camera * normalize(vec4(uv.x, uv.y, -FOCAL_DIST, 0.0)));
    ray.pos = vec3(camera[3]);

    Trace trace = march(ray);
    outColor = getColor(trace);
}