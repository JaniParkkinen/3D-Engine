#version 330

precision mediump float;

in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_FragPos;

in vec4 LightSpacePos;
in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in vec3 Tangent0;

//in vec3 N;
//in vec3 V;
//in vec3 E;
//in vec3 B;
//in vec3 T;

out vec4 gl_FragColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 transmittance;
uniform vec3 emission;
uniform vec3 shininess;
uniform vec3 ior;
uniform vec3 dissolve;

vec3 CalcBumpedNormal()
{
vec3 Normal = normalize(Normal0);
vec3 Tangent = normalize(Tangent0);
Tangent = normalize(Tangent - dot(Tangent, Normal)* Normal);
vec3 Bitangent = cross(Tangent, Normal);
//gNormalMap might be undefined;
vec3 BumpMapNormal = texture(gNormalMap, TexCoord0).xyz;
BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
vec3 NewNormal;
mat3 TBN = mat3(Tangent, Bitangent, Normal);
NewNormal = TBN * BumpMapNormal;
NewNormal = normalize(NewNormal);
return NewNormal;

}

uniform sampler2D tex;
uniform sampler2D normtex;

void main()
{
vec3 normal = CalcBumpedNormal();

//	mat3 TBN = mat3 (T, B, N);
//	
//	vec3 normal = normalize (texture2D(normtex, ex_TexCoord).xyz*2.0 - 1.0);
//	
//	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
//	vec3 ambientasd = ambient * vec3(1.0f, 1.0f, 1.0f);
//
//	vec3 norm = normalize(ex_Normal);
//	vec3 lightDir = normalize(vec3(-2.5f, 0.0f, 0.0f));
//	
//	vec3 L = lightDir.xyz - V;
//	L*=TBN;
//	
//	float dist = length(L);
//    L = normalize(L);
//	
//	float NdotL = max(dot(L,N),0.0);
//	float diff = max(dot(norm, lightDir), 0.0);
//    if(NdotL > 0)
//    {
//		float att = 1.0;
//        vec4 diffuse =  clamp(att*NdotL*diff,0,1);
//        color += att*gl_FrontLightProduct[i].ambient + diffuse;
//    }
//
//	vec3 diffuseasd = diff * lightColor;
//
//	vec3 viewDir = normalize(vec3(0.0f, 0.0f, 0.0f));
//	vec3 reflectionDir = normalize(-reflect(-lightDir, norm));
//
//	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 1);
//	vec3 specularasd = specular * spec * lightColor;
//
//	vec3 TextureNormal_tangentspace = texture(tex, ex_TexCoord).rgb;
//	TextureNormal_tangentspace = normalize(TextureNormal_tangentspace * 2.0 -1.0);
	gl_FragColor = N*V;
	//gl_FragColor = texture(normtex, ex_TexCoord);
	//gl_FragColor = vec4(((ambientasd + diffuseasd + specularasd) * gl_FragColor.xyz), 1.0f);
}