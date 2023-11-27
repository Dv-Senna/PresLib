#version 460

layout (location = 0) in vec2 in_TexCoord0;

layout (location = 0) out vec4 out_Color;

layout (binding = 0) uniform sampler2D texture0;
layout (std140, binding = 2) uniform uni_FramebufferColor
{
	vec4 uni_Color;
};


void main()
{
	out_Color = uni_Color * texture(texture0, in_TexCoord0);
}