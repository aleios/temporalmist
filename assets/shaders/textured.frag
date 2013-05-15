#version 400 core

in vec4 pass_Color;
in vec2 pass_TexCoord;

uniform sampler2D tex;

out vec4 out_Color;

void main(void)
{
	out_Color = texture(tex, pass_TexCoord) * vec4(pass_Color);
}