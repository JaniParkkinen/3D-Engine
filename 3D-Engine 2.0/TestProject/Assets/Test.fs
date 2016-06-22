#version 330

precision mediump float;

in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_FragPos;

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

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambientasd = ambient * vec3(1.0f, 1.0f, 1.0f);

	vec3 norm = normalize(ex_Normal);
	vec3 lightDir = normalize(vec3(-2.5f, 0.0f, 0.0f));

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseasd = diff * lightColor;

	vec3 viewDir = normalize(vec3(0.0f, 0.0f, 0.0f));
	vec3 reflectionDir = normalize(-reflect(-lightDir, norm));

	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 1);
	vec3 specularasd = specular * spec * lightColor;

	gl_FragColor = texture(tex, ex_TexCoord);
	gl_FragColor = vec4(((ambientasd + diffuseasd + specularasd) * gl_FragColor.xyz), 1.0f);
}