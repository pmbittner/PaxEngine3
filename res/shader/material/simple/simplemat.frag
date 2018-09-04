#version 400 core

in vec2 fragTextureCoords;
out vec4 out_Color;

uniform vec3  material_diffuse_color;
uniform vec3  material_specular_color;
uniform vec3  material_ambient_color;
uniform float material_specular_exponent;
uniform float material_opacity = 1;

uniform bool material_hasDiffuseTexture;
uniform sampler2D diffuseTexture;


void main(void) {
    vec4 clr = vec4(material_diffuse_color, 0);
    if (material_hasDiffuseTexture) {
        clr = texture(diffuseTexture, fragTextureCoords);
    }
	clr.w = material_opacity;

	out_Color = clr;
}