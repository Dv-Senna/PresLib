#version 460

layout (location = 0) in vec2 in_Pos;

layout (location = 0) out vec4 out_Color;

layout (std140, binding = 0) uniform uni_Vertices
{
	mat4 uni_Transformation;
	vec4 uni_Color;
	float uni_Fade;
};


void main()
{
	vec2 uv = in_Pos * 2.0 - 1.0;

	float distance = 1.0 - length(uv);
	vec4 color = vec4(1.0, 1.0, 1.0, smoothstep(0.0, uni_Fade, distance));

	out_Color = uni_Color * color;
}