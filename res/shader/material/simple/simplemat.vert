#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out ShaderData
{
  vec3 eyeDirection;
  vec3 normal;
  vec2 textureCoord;
} lightProperties;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 modelview;
uniform mat4 transposedInvModel;


void main(void) {
    lightProperties.eyeDirection = -view[3].xyz - (model * vec4(position, 1.0)).xyz;
    lightProperties.normal = (transposedInvModel * vec4(normal, 0)).xyz;
    lightProperties.textureCoord = uv;

    gl_Position = projection * modelview * vec4(position, 1.0);
}