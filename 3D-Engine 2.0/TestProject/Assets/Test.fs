#version 330

precision mediump float;

const int MAX_DIRECTIONAL_LIGHTS = 2;
const int MAX_POINT_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

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

struct BaseLight {
	vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
};

struct DirectionalLight
{
	BaseLight Base;
	vec3 Direction;
};

struct Attenuation
{
	float Constant;
	float Linear;
	float Exp;
};

struct PointLight
{
	BaseLight Base;
	vec3 Position;
	Attenuation Atten;
};

struct SpotLight
{
	struct PointLight Base;
	vec3 Direction;
	float Cutoff;
};

//Material
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 transmittance;
uniform vec3 emission;
uniform float shininess;
uniform float ior;
uniform float dissolve;

//Light
uniform int gNumDirectionalLight;
uniform DirectionalLight gDirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform int gNumPointLights;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform int gNumSpotLights;
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];

//Camera
uniform vec3 CameraPosition;

vec3 CalcBumpedNormal()
vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
	vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;
	float DiffuseFactor = dot(Normal, -LightDirection);
Tangent = normalize(Tangent - dot(Tangent, Normal)* Normal);
	vec4 DiffuseColor = vec4(0, 0, 0, 0);
	vec4 SpecularColor = vec4(0, 0, 0, 0);
vec3 BumpMapNormal = texture(gNormalMap, TexCoord0).xyz;
BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
vec3 NewNormal;
mat3 TBN = mat3(Tangent, Bitangent, Normal);
NewNormal = TBN * BumpMapNormal;
NewNormal = normalize(NewNormal);
return NewNormal;

	if (DiffuseFactor > 0) {
		DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor, 1.0f);
		vec3 VertexToEye = normalize(CameraPosition - ex_FragPos);
		vec3 LightReflect = normalize(reflect(LightDirection, Normal));
		float SpecularFactor = dot(VertexToEye, LightReflect);
		if (SpecularFactor > 0) {
			SpecularFactor = pow(SpecularFactor, 32);
			SpecularColor = vec4(Light.Color * specular * SpecularFactor, 1.0f);
		}
	}

	return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcDirectionalLight(struct DirectionalLight l, vec3 Normal)
{
	return CalcLightInternal(l.Base, l.Direction, Normal);
}

vec4 CalcPointLight(struct PointLight l, vec3 Normal)
{
	vec3 LightDirection = ex_FragPos - l.Position;
	float Distance = length(LightDirection);
	LightDirection = normalize(LightDirection);

	vec4 Color = CalcLightInternal(l.Base, LightDirection, Normal);
	float Attenuation = l.Atten.Constant +
		l.Atten.Linear * Distance +
		l.Atten.Exp * Distance * Distance;

	return Color / Attenuation;
}

vec4 CalcSpotLight(struct SpotLight l, vec3 Normal)
{
	vec3 LightToPixel = normalize(ex_FragPos - l.Base.Position);
	float SpotFactor = dot(LightToPixel, l.Direction);

	if (SpotFactor > l.Cutoff) {
		vec4 Color = CalcPointLight(l.Base, Normal);
		return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));
	}
	else {
		return vec4(0,0,0,0);
	}
}

void main()
{
	vec3 Normal = normalize(ex_Normal);
	vec4 TotalLight = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < gNumDirectionalLight; i++) {
		TotalLight += CalcDirectionalLight(gDirectionalLights[i], Normal);
	}

	for (int i = 0 ; i < gNumPointLights ; i++) {
		TotalLight += CalcPointLight(gPointLights[i], Normal);
	}
	
	for (int i = 0 ; i < gNumSpotLights ; i++) {
		TotalLight += CalcSpotLight(gSpotLights[i], Normal);
	}

	gl_FragColor = texture2D(tex, ex_TexCoord) * TotalLight;
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
