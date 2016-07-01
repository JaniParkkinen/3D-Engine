#version 330

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Bitangent;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;

out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_FragPos;

out vec4 ex_LightSpacePos;
out vec2 ex_TexCoord0;
out vec3 ex_Normal0;
out vec3 ex_WorldPos0;
out vec3 ex_Tangent0;

//out vec3 N;
//out vec3 V;
//out vec3 E;
//out vec3 T;
//out vec3 B;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_NormalMatrix;

uniform mat4 gWVP;
uniform mat4 gLightWVP;
uniform mat4 gWorld;

void main() {
	gl_position = gWVP * vec4(Position, 1.0);
	ex_Normal = transpose(mat3(View)*inverse(mat3(Model))) * in_Normal;
	ex_FragPos = mat3(Model) * in_Position;
	ex_Normal0 = (gWorld * vec4(normal, 0.0)).xyz;
	ex_Tangent0 = (gWorld * vec4(tangent, 0.0)).xyz;
	ex_WorldPos0 = (gWorld * vec4(Position, 1.0)).xyz;

	gl_Position = (Projection * View * Model) * vec4(in_Position, 1.0f);
	//mat4 asd = Model * View;
	//N = mat3(transpose(inverse(asd))) * in_Normal;
    //V = vec3(Model*View*vec4(in_Position, 1));
    //E = normalize(-V);
    //
    //T = normalize(transpose(inverse(Model*View))*tangent);
    //B = normalize(transpose(inverse(Model*View))*bitangent);
	
	//ex_TexCoord = in_TexCoord;
	//ex_Normal = mat3(transpose(inverse(Model))) * in_Normal;
	//ex_FragPos = vec3(Model * vec4(in_Position, 1.0f));
	
	//gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
}

	//ex_Normal = transpose(inverse(mat3(Model))) * in_Normal;
	//ex_FragPos = mat3(Model) * in_Position;