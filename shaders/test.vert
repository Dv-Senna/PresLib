#version 460


layout (location = 0) in vec2 in_Pos;
layout (location = 1) in vec2 in_TexCoord0;

layout (location = 0) out vec2 out_TexCoord0;

layout (std140, binding = 0) uniform uni_Color
{
	float r;
	float g;
	float b;
	mat4 scale;
};


void main()
{
	gl_Position = scale * vec4(in_Pos, 0.0, 1.0);
	out_TexCoord0 = in_TexCoord0;
}