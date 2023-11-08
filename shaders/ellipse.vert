#version 460

layout (location = 0) in vec2 in_Pos;

layout (location = 0) out vec2 out_Pos;

layout (std140, binding = 0) uniform uni_Vertices
{
	mat4 uni_Transformation;
	vec4 uni_Color;
	float uni_Fade;
};


void main()
{
	gl_Position = uni_Transformation * vec4(in_Pos, 0, 1);
	out_Pos = in_Pos;
}