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
out vec4 vcolor;
#endif

layout (location=0) in vec4 position;

void main()
{
#if defined(_DEBUG_VERSION)
	 vcolor = position;
	 //vcolor.x = Scene.proj[0][0];
	 //vcolor.y = Scene.proj[0][1];
	 //vcolor.z = Scene.proj[0][2];
#endif

	// gl_Position = Model.model * position ;
	// gl_Position = Scene.view * Model.model * position ;
	// gl_Position = Scene.proj * Scene.view * Model.model * position ;

	// gl_Position = Scene.view * Model.model * position ;
	gl_Position = Scene.proj * Scene.view * Model.model * position ;

} 
