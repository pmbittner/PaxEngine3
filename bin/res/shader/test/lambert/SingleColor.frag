#version 400 core
// FRAGMENT SHADER
#define PLCOUNT 1

in vec3 surfaceNormal;
in vec3 lightVec[PLCOUNT];
in vec2 fragTextureCoords;

out vec4 out_Color;

uniform vec3 pLightColors[PLCOUNT];
uniform float pLightIntensity[PLCOUNT];

uniform vec3 mat_diffuseColor;

uniform sampler2D textureSampler;

void main(void) {
    vec3 normalVector = normalize(surfaceNormal);
    vec3 diffuse = vec3(.5);

    for (int i = 0; i < PLCOUNT; i++) {
        float distanceToLight = length(lightVec[i]);

        diffuse +=
            max(
                dot(normalize(lightVec[i]), normalVector),
                0
            )
            //* (1 / (distanceToLight * distanceToLight))
            * pLightIntensity[i] * pLightColors[i];
    }

    diffuse *= mat_diffuseColor * texture(textureSampler, fragTextureCoords).xyz;
    vec4 shadedColor = vec4(diffuse, 1.0);
	out_Color =  shadedColor;
}