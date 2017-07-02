#version 400 core
// VERTEX SHADER
#define PLCOUNT 1

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec3 surfaceNormal;
out vec3 toCameraVector;
out vec3 lightVec[PLCOUNT];
out vec2 fragTextureCoords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 transposedInvModelView;

uniform vec3 pLightPositions[PLCOUNT];

void main(void) {
    vec4 worldPosition = modelview * vec4(position, 1.0);
    toCameraVector = -worldPosition.xyz;

    surfaceNormal = (transposedInvModelView * vec4(normal, 0.0)).xyz;

    for (int i = 0; i < PLCOUNT; i++) {
        vec4 lightInCamSpace = view * vec4(pLightPositions[i], 1.0);
        lightVec[i] = (lightInCamSpace - worldPosition).xyz;
    }

    fragTextureCoords = texCoords;
    gl_Position = projection * worldPosition;
}