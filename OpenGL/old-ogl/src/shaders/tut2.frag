#version 330

#define _DEBUG_VERSION

layout (std140) uniform ModelBlock {
	mat4 model;
} Model ;

layout (std140) uniform SceneBlock {
	mat4 view;
	mat4 proj;
} Scene ;

layout (std140) uniform MaterialBlock {
	vec4 color;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} Material;

layout (std140) uniform LightBlock {
	vec4 lposition;
	vec4 lcolor;
} Light;

#if defined(_DEBUG_VERSION)
in  vec4 vcolor;
#endif

out vec4 f_color;

void main()
{
#if defined(_DEBUG_VERSION)
	f_color = vcolor;
#else
	f_color = Material.color;
#endif
}
