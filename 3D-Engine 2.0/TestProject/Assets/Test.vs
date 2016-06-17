#version 330

in vec3 in_Position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(in_Position, 1.0);
}