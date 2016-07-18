#version 330

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;
//in ivec4 in_BoneIDs;
//in vec4 in_Weights;

out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_FragPos;

const int MAX_BONES = 100;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
//uniform mat4 gBones[MAX_BONES];

void main() {
	//mat4 BoneTransform = gBones[in_BoneIDs[0]] * in_Weights[0];
	//BoneTransform += gBones[in_BoneIDs[1]] * in_Weights[1];
	//BoneTransform += gBones[in_BoneIDs[2]] * in_Weights[2];
	//BoneTransform += gBones[in_BoneIDs[3]] * in_Weights[3];

	//vec4 PosL = BoneTransform * vec4(in_Position, 1.0);
	//vec4 NormalL = BoneTransform * vec4(in_Normal, 0.0);
	ex_TexCoord = in_TexCoord;
	//Muokattu NormalL
	ex_Normal = mat3(transpose(inverse(Model))) * in_Normal;
	ex_FragPos = vec3(Model * vec4(in_Position, 1.0f));
	
	//muokattu PosL
	gl_Position = Projection * View * Model * vec4(in_Position, 1.0f);
}
