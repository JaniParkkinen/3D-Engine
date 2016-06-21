#version 330

precision mediump float;

in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_FragPos;

out vec4 gl_FragColor;

uniform sampler2D tex;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = 0.25f * vec3(1.0f, 1.0f, 1.0f);

	vec3 norm = normalize(ex_Normal);
	vec3 lightDir = normalize(vec3(-2.5f, 0.0f, 0.0f));

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(vec3(0.0f, 0.0f, 0.0f));
	vec3 reflectionDir = normalize(-reflect(-lightDir, norm));

	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 1);
	vec3 specular = 0.1f * spec * lightColor;

	gl_FragColor = texture(tex, ex_TexCoord);
	gl_FragColor = vec4(((ambient + diffuse + specular) * gl_FragColor.xyz), 1.0f);
}