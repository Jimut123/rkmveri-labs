#version 330

#define _DEBUG_VERSION

layout (std140) uniform ModelBlock {
	mat4 model;
	mat4 normal;
} Model ;

layout (std140) uniform SceneBlock {
	mat4 view;
	mat4 proj;
        vec4 camera_pos;
} Scene ;

#if defined(_DEBUG_VERSION)
out vec4 vcolor;
out vec4 ncolor;
#endif

layout (location=0) in vec4 vposition;
layout (location=1) in vec2 vtcoord;
layout (location=2) in vec3 vnormal;

out vec4 fposition;
out vec2 ftcoord;
out vec3 fnormal;


void main()
{
#if defined(_DEBUG_VERSION)
	 vcolor = vposition;
         ncolor.rgb = vnormal;
         ncolor.a = 1.0;

	 //vcolor.x = Scene.proj[0][0];
	 //vcolor.y = Scene.proj[0][1];
	 //vcolor.z = Scene.proj[0][2];
#endif

	// gl_Position = Model.model * vposition ;
	// gl_Position = Scene.view * Model.model * vposition ;
	// gl_Position = Scene.proj * Scene.view * Model.model * vposition ;

	gl_Position = Scene.proj * Scene.view * Model.model * vposition ;

	ftcoord = vtcoord;
        fposition = Model.model*vposition;

        vec4 wnormal;
        vec4 zero = vec4(0.0,0.0,0.0,1.0);

        wnormal.xyz = vnormal;
        wnormal.w = 1.0;

        fnormal = vec3(Model.normal * wnormal);

        fnormal = normalize(fnormal);

} 
