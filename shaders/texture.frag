#version 460


layout (location = 0) in vec2 in_texCoord0;

layout (location = 0) out vec4 out_Color;


layout (binding = 0) uniform sampler2D uni_texture0;


void main() {
	out_Color = texture(uni_texture0, in_texCoord0);
}