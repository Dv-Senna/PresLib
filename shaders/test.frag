#version 460


layout (location = 0) in vec2 in_TexCoord0;

layout (location = 0) out vec4 out_Color;

layout (std140, binding = 0) uniform uni_Color
{
	float r;
	float g;
	float b;
	mat4 scale;
};

layout (binding = 0) uniform sampler2D texture0;

void main()
{
	out_Color = texture(texture0, in_TexCoord0);
	//out_Color = vec4(in_Color, 1.0);
}