#version 330 core

out vec4 fcolor;

uniform vec4 color;

void main()
{
	fcolor = color;
	fcolor.a = 0.5;
}
