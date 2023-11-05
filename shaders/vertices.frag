#version 460

layout (location = 0) out vec4 out_Color;

layout (std140, binding = 0) uniform uni_Vertices
{
	mat4 uni_Transformation;
	vec4 uni_Color;
};


void main()
{
	out_Color = uni_Color;
}