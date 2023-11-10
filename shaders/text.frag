#version 460

layout (location = 0) in vec2 in_TexCoord0;

layout (location = 0) out vec4 out_Color;


layout (std140, binding = 0) uniform uni_Text
{
	mat4 uni_Transformation;
	vec4 uni_Color;
};

layout (binding = 0) uniform sampler2D uni_Texture0;


void main()
{
	out_Color = uni_Color * vec4(1.0, 1.0, 1.0, texture(uni_Texture0, in_TexCoord0).r);
}