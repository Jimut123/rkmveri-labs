#version 330 core

layout(location = 0) in vec3 vposition;

void main(){
	gl_Position.xyz = vposition;
	gl_Position.w = 1.0;
}
