#version 330

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;

uniform mat4 gWVP;
uniform mat4 gLightWVP;
uniform mat4 gWorld;

out vec4 ex_LightSpacePos;
out vec3 ex_WorldPos;
out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_Tangent;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gWVP = Model * View * Projection;
	gl_Position		= gWVP * vec4(in_Position, 1.0);
	LightSpacePos	= gLightWVP * vec4(in_Position, 1.0);
	ex_TexCoord		= in_TexCoord;
	ex_Normal		= (gWorld * vec4(in_Normal, 0.0)).xyz;
	ex_Tangent		= (gWorld * vec4(in_Tangent, 0.0)).xyz;
	ex_WorldPos		= (gWorld * vec4(in_Position, 1.0)).xyz;
}
//vanha
#version 330

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;

uniform mat4 gWVP;
uniform mat4 gLightWVP;
uniform mat4 gWorld;

//out vec4 LightSpacePos;
//out vec2 TexCoord0;
//out vec3 Normal0;
//out vec3 WorldPos0;
//out vec3 Tangent0;

out vec2 ex_TexCoord;
out vec3 ex_Normal;
//out vec3 ex_FragPos;
out vec3 ex_Tangent;

//uniform mat4 Model;
//uniform mat4 View;
//uniform mat4 Projection;

void main()
{
	gl_Position		= gWVP * vec4(in_Position, 1.0);
	//LightSpacePos	= gLightWVP * vec4(in_Position, 1.0);
	ex_TexCoord		= in_TexCoord;
	ex_Normal		= (gWorld * vec4(in_Normal, 0.0)).xyz;
	ex_Tangent		= (gWorld * vec4(in_Tangent, 0.0)).xyz;
	//WorldPos0		= (gWorld * vec4(in_Position, 1.0)).xyz;


	//mat4 gWVP = Model * View * Projection;
	//mat4 gWorld = Model;

	//gl_position = gWVP * vec4(in_Position, 1.0);
	//ex_TexCoord = in_TexCoord;
	//ex_Normal = vec3(gWorld * vec4(in_Normal, 0.0));
	//ex_Normal = mat3(transpose(inverse(Model))) * in_Normal;
	//ex_FragPos = vec3(Model * vec4(in_Position, 1.0f));
	//ex_Tangent = vec3(gWorld * vec4(in_Tangent, 0.0));
	////ex_WorldPos0 = (gWorld * vec4(in_Position, 1.0)).xyz;
	
	//gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
}