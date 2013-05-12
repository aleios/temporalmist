#version 430 core

in vec4 pass_Color;

out vec4 out_Color;

void main(void)
{
	out_Color = vec4(pass_Color);
}