#version 400 core


out vec4 outColor;

uniform mat4 camera;
uniform vec2 resolution;

#define SAMPLES_PER_PIXEL_SIDE 2



/// Definitions


#define RGB_BYTES(r, g, b) vec4(r, g, b, 1) / vec4(255, 255, 255, 1);

/// Fractal Params
#define MANDELBROT_ITERATIONS 2000

// complex number arithmetics

// complex addition and substraction are the same as for vec2.

vec2 complex_multiply(in vec2 a, in vec2 b) {
    return vec2(
        a.x*b.x - a.y*b.y,
        a.x*b.y + a.y*b.x
    );
}

vec2 complex_sqrt(in vec2 a) {
    return vec2(
        a.x*a.x - a.y*a.y,
        2*a.x*a.y
    );
}

// coloring
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 iterationToColor(float iteration) {
    //float h = float(iteration) / float(MANDELBROT_ITERATIONS);
    //float s = 0.7 * float(MANDELBROT_ITERATIONS - iteration) / float(iteration);
    
    float h = 0.5 + 0.5*cos(log(log(iteration)));
    float s = 0.7;
    float v = 0.9;
    return vec4(hsv2rgb(vec3(h, s, v)), 1);
}

vec2 pixelToCoords(vec2 pixel) {
    float zoom = camera[3][1];
    zoom = pow(4, zoom);// * zoom * zoom * zoom;
    
    vec2 pos = (camera * vec4(pixel.x, 0, -pixel.y, 1)).xz;
    vec2 center = camera[3].xz;// = (camera * vec4(0, 0, 0, 1)).xz;
    return center + (pos - center) / zoom;
}

vec4 mandelbrot(vec2 pixel) {
    /// Mandelbrot Set
    //*
    vec2 c = pixelToCoords(pixel);
    vec2 z = vec2(0);
    /*/
    /// Various Julia Sets
    vec2 z = pixelToCoords(pixel);
    vec2 c = vec2(-0.8, 0.2);//vec2(0);
    //*/
    
    for (int i = 0; i < MANDELBROT_ITERATIONS; ++i) {
        z = complex_sqrt(z) + c;
        
        if (length(z) > 2) {
            float smoothIt = float(i) - log2(log2(dot(z,z))) + 4.0;
            return iterationToColor(smoothIt);
        }
    }
    
    return vec4(0, 0, 0, 1);
}

void main(void) {
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

            color += mandelbrot(vec2(screen.x + xOffset, screen.y + yOffset));
        }
    }

    outColor = color / (SAMPLES_PER_PIXEL_SIDE * SAMPLES_PER_PIXEL_SIDE);
}