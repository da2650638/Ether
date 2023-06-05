#version 450 core
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform float u_TilingFactor;

in vec4 v_Color;
in vec2 v_TexCoord;

void main()
{
	color = texture(u_Texture, v_TexCoord * u_TilingFactor) * v_Color;
}