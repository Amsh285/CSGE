#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 vColor;
out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_MVP * u_Transform * position;
	vColor = color;
	v_TexCoord = texCoord;
}
