#version 330 core
out vec4 FragColor;
uniform sampler2D sampler;
uniform int sign;
in vec3 color;
in vec2 uv;
void main(){
	if (sign != 0){
		FragColor=texture(sampler,uv);
	}
	else {
		FragColor = vec4(color,0.5f);
	}
}