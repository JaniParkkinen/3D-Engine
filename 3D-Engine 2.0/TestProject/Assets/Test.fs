#version 330

precision mediump float;

const int MAX_POINT_LIGHTS = 2;

in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_FragPos;

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
uniform int numDirLight;
uniform DirectionalLight gDirectionalLight;
uniform int gNumPointLights;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];

//Camera
uniform vec3 CameraPosition;

uniform sampler2D tex;

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
	vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;
	float DiffuseFactor = dot(Normal, -LightDirection);

	vec4 DiffuseColor = vec4(0, 0, 0, 0);
	vec4 SpecularColor = vec4(0, 0, 0, 0);

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

vec4 CalcDirectionalLight(vec3 Normal)
{
	return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal);
}

vec4 CalcPointLight(int Index, vec3 Normal)
{
	vec3 LightDirection = ex_FragPos - gPointLights[Index].Position;
	float Distance = length(LightDirection);
	LightDirection = normalize(LightDirection);

	vec4 Color = CalcLightInternal(gPointLights[Index].Base, LightDirection, Normal);
	float Attenuation = gPointLights[Index].Atten.Constant +
						gPointLights[Index].Atten.Linear * Distance +
						gPointLights[Index].Atten.Exp * Distance * Distance;

	return Color / Attenuation;
}

void main()
{
	vec3 Normal = normalize(ex_Normal);
	vec4 TotalLight = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < numDirLight; i++) {
		TotalLight += CalcDirectionalLight(Normal);
	}

	for (int i = 0 ; i < gNumPointLights ; i++) {
		TotalLight += CalcPointLight(i, Normal);
	}

	gl_FragColor = texture2D(tex, ex_TexCoord) * TotalLight;
}
