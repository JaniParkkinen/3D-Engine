#version 330

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Bitangent;

out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_FragPos;
out mat3 TBN;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	mat3 MV3x3 = mat3(Model*View);
	vec3 tangent_Cameraspace = MV3x3 * normalize(in_Tangent);
	vec3 bitangent_Cameraspace = MV3x3 * normalize(in_Bitangent);
	vec3 normal_Cameraspace = MV3x3 * normalize(in_Normal);
		
	mat3 TBN = transpose(mat3(
		tangent_Cameraspace,
		bitangent_Cameraspace,
		normal_Cameraspace));
	
	ex_TexCoord = in_TexCoord;
	ex_Normal = mat3(transpose(inverse(Model))) * in_Normal;
	ex_FragPos = vec3(Model * vec4(in_Position, 1.0f));
	
	gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
}