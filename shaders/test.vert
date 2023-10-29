#version 460


layout (location = 0) in vec2 in_Pos;
layout (location = 1) in vec3 in_Color;

layout (location = 0) out vec3 out_Color;


void main()
{
	gl_Position = vec4(in_Pos, 0.0, 1.0);
	out_Color = in_Color;
}