#version 460


layout (location = 0) in vec2 in_Pos;

layout (location = 0) out vec2 out_TexCoord0;


layout (std140, binding = 0) uniform uni_Texture
{
	mat4 uni_Transformation;
	vec4 uni_Color;
};


void main()
{
	gl_Position = uni_Transformation * vec4(in_Pos, 0, 1);
	out_TexCoord0 = in_Pos;
}