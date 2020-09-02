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

#if defined(_DEBUG_VERSION)
in  vec4 vcolor;
in  vec4 ncolor;
#endif

in vec2 ftcoord;
in vec3 fnormal;
in vec4 fposition;

out vec4 f_color;

uniform sampler2D basetex;
uniform sampler2D texttex;

vec3 shade(vec3 p, vec3 n)
{
    vec3 v = normalize(Scene.camera_pos.xyz - p);

    vec3 t_color;

    vec2 tc;

    //tc[0] = Material.texorigin[0] + ftcoord[0]*Material.texsize[0];
    //tc[1] = Material.texorigin[1] + ftcoord[1]*Material.texsize[1];

    t_color = texture(basetex,Material.texorigin.xy + fract(ftcoord)*Material.texsize.xy).rgb;


    vec3 Lo = t_color * Light.ambience;

    for (uint k = 0u; k < Light.num; k++)
    {
	vec3 l = normalize(Light.light_pos[k] - p);
	vec3 h = normalize(v + l);
        n = normalize(n);
	float cosTh = clamp(dot(n, h), 0.0, 1.0);
	float cosTi = clamp(dot(n, l), 0.0, 1.0);
	Lo += (t_color 
                   + Material.specular.rgb 
                        * clamp(pow(cosTh, 0.0000001+Material.shininess),0.0,1.0)) 
              * Light.emission[k] * cosTi;

    }
    return Lo;
}

void main()
{
#if defined(_DEBUG_VERSION)

    f_color.rgb = shade(fposition.xyz, fnormal.xyz);

    //f_color = vcolor;

    //f_color.rgb = normalize(fnormal);
    //f_color.rgb = fnormal;
    //f_color.rgb = 0.2*fposition.xyz;
    f_color.a = 1.0;
    //f_color.b = 0.0;

    //f_color.rg = Material.texsize.rg;

    //f_color.xy = ftcoord;

    //f_color.zw = ftcoord;

    //f_color =  texture(basetex,ftcoord);

    //f_color.rgb = vec3(0.5,0.5,0.5)+0.5*normalize(Light.light_pos[0]-fposition.xyz);
    // vec3 l = normalize(Light.light_pos[0]-fposition.xyz);
    // vec3 n = normalize(fnormal);

    //f_color.rgb = normalize(l);
    //float cti = dot(normalize(fnormal), normalize(l));
    //f_color.rgb = vec3(cti, cti, cti);
    //f_color.rgb = normalize(fnormal.xyz);
    //f_color.rgb = ncolor.rgb;

#else

    f_color.a = 1.0;
    f_color.rgb = shade(fposition.xyz, fnormal.xyz);

#endif

}
