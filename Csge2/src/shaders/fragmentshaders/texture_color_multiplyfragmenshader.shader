#version 330 core

in vec4 vColor;
in vec2 v_TexCoord;

out vec4 color;

uniform sampler2D tex1;

void main()
{
	color =	texture(tex1, v_TexCoord) * vColor;
}