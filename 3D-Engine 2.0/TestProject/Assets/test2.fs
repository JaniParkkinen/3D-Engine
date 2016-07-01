#version 330

precision mediump float;

in vec4 in_LightSpacePos;
in vec3 in_WorldPos;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;

out vec4 gl_FragColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 transmittance;
uniform vec3 emission;
uniform vec3 shininess;
uniform vec3 ior;
uniform vec3 dissolve;

uniform sampler2D tex;
uniform sampler2D normtex;

vec3 CalcBumpedNormal()
{
	vec3 Normal = normalize(in_Normal);
	vec3 Tangent = normalize(in_Tangent);
	
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
	vec3 Bitangent = cross(Tangent, Normal);
	
	vec3 BumpMapNormal = tex(normtex, in_TexCoord).xyz;
	BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
	
	vec3 NewNormal;
	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	
	NewNormal = TBN * BumpMapNormal;
	NewNormal = normalize(NewNormal);
	
	return NewNormal;
}

void main()
{
	vec3 Normal = CalcBumpedNormal();
}

#version 330

//in vec4 in_LightSpacePos;
//in vec2 in_texCoord0;
//in vec3 in_Normal0;
//in vec3 in_WorldPos0;
//in vec3 in_Tangent;

precision mediump float;

in vec2 ex_texcoord;
in vec3 ex_normal;
//in vec3 ex_fragpos;
in vec3 ex_tangent;

out vec4 gl_FragColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 transmittance;
uniform vec3 emission;
uniform vec3 shininess;
uniform vec3 ior;
uniform vec3 dissolve;

uniform sampler2D tex;
uniform sampler2D normtex;

vec3 CalcBumpedNormal()
{
	vec3 Normal = normalize(ex_normal);
	vec3 Tangent = normalize(ex_tangent);
	
	Tangent = normalize(Tangent - dot(Tangent, Normal)* Normal);
	vec3 Bitangent = cross(Tangent, Normal);
	
	vec3 BumpMapNormal = tex(normtex, ex_TexCoord).xyz;
	BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
	
	vec3 NewNormal;
	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	
	NewNormal = TBN * BumpMapNormal;
	NewNormal = normalize(NewNormal);
	
	return NewNormal;
}

void main()
{
	vec3 normal = CalcBumpedNormal();

	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambientasd = ambient * vec3(1.0f, 1.0f, 1.0f);

	vec3 lightDir = normalize(vec3(-2.5f, 0.0f, 0.0f));

	vec3 diffuseasd = diffuse * lightColor;

	vec3 viewDir = normalize(vec3(0.0f, 0.0f, 0.0f));
	vec3 reflectionDir = normalize(-lightDir, normal);

	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 1);
	vec3 specularasd = specular * spec * lightColor;

	gl_FragColor = texture(tex, ex_TexCoord);
	gl_FragColor = vec4(((ambientasd + diffuseasd + specularasd) * gl_FragColor.xyz), 1.0f);
}