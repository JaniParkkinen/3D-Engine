#version 330

in vec3 in_Position;
in vec2 in_TexCoord;

out vec2 ex_TexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	ex_TexCoord = in_TexCoord;
	gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
}