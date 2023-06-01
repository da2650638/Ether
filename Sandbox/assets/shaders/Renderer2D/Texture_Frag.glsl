#version 450 core
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec2 v_TexCoord;

void main()
{
	color = texture(u_Texture, v_TexCoord * 10.0f) * u_Color;
}