#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out ShaderData
{
  vec3 eyeDirection;
  vec3 normal;
  vec2 textureCoord;
} vs_out;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 modelview;
uniform mat4 transposedInvModelView;


void main(void) {
    vs_out.eyeDirection = inverse(view)[3].xyz - (model * vec4(position, 1.0)).xyz;
    vs_out.normal = (transposedInvModelView * vec4(normal, 0)).xyz;
    vs_out.textureCoord = uv;

    gl_Position = projection * modelview * vec4(position, 1.0);
}