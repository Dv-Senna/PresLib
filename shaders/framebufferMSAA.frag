#version 460

layout (location = 0) in vec2 in_TexCoord0;

layout (location = 0) out vec4 out_Color;


layout (std140, binding = 0) uniform uni_WindowFramebufferBlock
{
	float uni_SamplesCount;
	vec2 uni_ViewportSize;
};
layout (std140, binding = 2) uniform uni_FramebufferColor
{
	vec4 uni_Color;
};

layout (binding = 0) uniform sampler2DMS texture0;


void main()
{
	ivec2 normalizedTexCoord0 = ivec2(int(uni_ViewportSize.x * in_TexCoord0.x), int(uni_ViewportSize.y * in_TexCoord0.y));

	vec4 color = vec4(0.0);
	for (int i = 0; i < uni_SamplesCount; i++)
		color += texelFetch(texture0, normalizedTexCoord0, i);

	out_Color = uni_Color * color / uni_SamplesCount;
}