#version 460


layout (location = 0) in vec2 in_Pos;
layout (location = 1) in vec2 in_TexCoord0;

layout (location = 0) out vec2 out_TexCoord0;

layout (std140, binding = 1) uniform uni_FramebufferTransformation
{
	mat4 uni_Transformation;
};


void main()
{
	gl_Position = uni_Transformation * vec4(in_Pos, 0, 1);
	out_TexCoord0 = in_TexCoord0;
}
