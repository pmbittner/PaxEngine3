#version 400 core

in ShaderData
{
  vec3 eyeDirection;
  vec3 normal;
  vec2 textureCoord;
} lightProperties;

out vec4 out_Color;


/// LIGHT
#define NUM_MAX_LIGHTS 8
#define BLINN_PHONG_SHADING 1

struct AmbientLight {
    vec3 color;
};

struct DirectionalLight {
    vec4 color;
    vec3 direction;
};

uniform struct Lights {
    AmbientLight ambient;

    int num_directional_lights;
    DirectionalLight directionals[NUM_MAX_LIGHTS];
} lights;


/// MATERIAL

uniform vec3  material_diffuse_color;
uniform vec3  material_specular_color;
uniform vec3  material_ambient_color;
uniform float material_specular_exponent;
uniform float material_opacity = 1;
uniform bool material_hasDiffuseTexture;
uniform sampler2D diffuseTexture;


void main(void) {
//*
    vec3 E = normalize(lightProperties.eyeDirection);
    vec3 N = normalize(lightProperties.normal);

    vec3 ambientTerm = vec3(0);
    vec3 diffuseTerm = vec3(0);
    vec3 specularTerm = vec3(0);
    vec3 L, H;
    float dotLN;

    ambientTerm += lights.ambient.color.xyz;

    for (int i = 0; i < lights.num_directional_lights; i++) {
        L = normalize(-lights.directionals[i].direction);
        dotLN = max(0, dot(L, N));
        //ambientTerm += lights.directionals[i].ambientColor;
        if (dotLN > 0) {
            diffuseTerm += lights.directionals[i].color.xyz * dotLN;

            // TODO: Use specular color here instead of plain color
            //#if PHONG_SHADING
            vec3 reflectDir = reflect(-L, N);
            // Sometimes I experienced negative terms here. Dont know why
            specularTerm += max(vec3(0, 0, 0), lights.directionals[i].color.xyz * pow(max(dot(reflectDir, E), 0), material_specular_exponent * 0.25) * dotLN);

            //#elif BLINN_PHONG_SHADING
            //H = normalize(E + L);
            //specularTerm += lights.directionals[i].color.w * lights.directionals[i].color.xyz * pow(max(dot(H, N), 0), material_specular_exponent) * dotLN;
            //#endif
        }
    }

    ambientTerm *= material_ambient_color;

    if (!material_hasDiffuseTexture) {
      diffuseTerm *= material_diffuse_color;
    }

    specularTerm *= material_specular_color;

    out_Color = vec4(ambientTerm + diffuseTerm + specularTerm, 1);

    if (material_hasDiffuseTexture) {
        vec4 texColor = texture(diffuseTexture, lightProperties.textureCoord);
        out_Color.rgb *= texColor.rgb;
    }

    // DEBUG
    //out_Color = vec4(lights.directionals[0].color.xyz, 1);
    /*/
    vec4 clr = vec4(material_diffuse_color, 0);
    if (material_hasDiffuseTexture) {
        clr = texture(diffuseTexture, fs_in.textureCoord);
    }
    clr.w = material_opacity;

    out_Color = clr;
    //*/
}