#version 150

in vec3 colour;

out vec4 out_Color;

void main(void){

	out_Color = vec4(colour,1.0);

}

