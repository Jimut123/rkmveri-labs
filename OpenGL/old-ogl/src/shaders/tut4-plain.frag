#version 330

#define _DEBUG_VERSION

#define MAXLIGHTS 4

layout (std140) uniform MaterialBlock {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
        vec2 texorigin;
        vec2 texsize;
} Material;

layout (std140) uniform SceneBlock {
	mat4 view;
	mat4 proj;
	vec4 camera_pos;
} Scene ;

layout (std140) uniform LightBlock {
    vec3 ambience;
    vec3 emission[MAXLIGHTS];
    vec3 light_pos[MAXLIGHTS];
    uint num;
} Light;

vec3 shade(vec3 p, vec3 n)
{
    vec3 v = normalize(Scene.camera_pos.xyz - p);

    vec3 Lo = Material.ambient.rgb * Light.ambience;

    for (uint k = 0u; k < Light.num; k++)
    {
	vec3 l = normalize(Light.light_pos[k] - p);
	vec3 h = normalize(v + l);
	float cosTh = clamp(dot(n, h), 0.0, 1.0);
	float cosTi = clamp(dot(n, l), 0.0, 1.0);
	Lo += (Material.diffuse.rgb
            + Material.specular.rgb * pow(cosTh, 0.0000001+ Material.shininess)) 
            * Light.emission[k] * cosTi;
    }
    return Lo;
}

#if defined(_DEBUG_VERSION)
in  vec4 vcolor;
in  vec4 ncolor;
#endif

in vec2 ftcoord;
in vec3 fnormal;
in vec4 fposition;

out vec4 f_color;

void main()
{
#if defined(_DEBUG_VERSION)
    //f_color = vcolor;

    //f_color.rgb = fnormal;
    f_color.a = 1.0;


    //f_color.xy = ftcoord;

    //f_color = ncolor;
    //f_color.zw = ftcoord;

    //f_color =  texture(basetex,ftcoord);
    f_color.rgb = shade(fposition.xyz, fnormal.xyz);
 
#else

    f_color.rgb = shade(fposition.xyz, fnormal.xyz);

#endif

}
