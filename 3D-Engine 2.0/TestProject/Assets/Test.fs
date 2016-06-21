#version 330

precision mediump float;

in vec2 ex_TexCoord;

out vec4 gl_FragColor;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, ex_TexCoord);
}