#version 460 core
layout (location =0) in vec3 aPos;
layout (location =1) in vec3 aColor;
layout (location =2) in vec2 aUV;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
out vec3 color;
out vec2 uv;
void main(){

	gl_Position = proj *view* model  * vec4( aPos,1.0);
	color=aColor;
	uv=aUV;
}