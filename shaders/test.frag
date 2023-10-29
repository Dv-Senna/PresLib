#version 460


layout (location = 0) in vec3 in_Color;

layout (location = 0) out vec4 out_Color;

layout (std140, binding = 0) uniform uni_Color
{
	float r;
	float g;
	float b;
	mat4 scale;
};

void main()
{
	out_Color = vec4(r, g, b, 1.0);
	//out_Color = vec4(in_Color, 1.0);
}