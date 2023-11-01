#version 460


layout (location = 0) in vec2 in_Pos;
layout (location = 1) in vec2 in_TexCoord0;

layout (location = 0) out vec2 out_TexCoord0;


void main()
{
	gl_Position = vec4(in_Pos, 0, 1);
	out_TexCoord0 = in_TexCoord0;
}
