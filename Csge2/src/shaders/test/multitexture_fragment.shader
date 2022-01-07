#version 330 core

in vec4 vColor;
in vec2 v_TexCoord;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
	vec4 col1 = texture(tex1, v_TexCoord);
	vec4 col2 = texture(tex2, v_TexCoord);

	color =	mix(col1, col2, 0.2);
}