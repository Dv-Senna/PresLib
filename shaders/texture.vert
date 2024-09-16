#version 460

layout (std140, binding = 0) uniform uni_Buffer {
	vec2 uni_viewportSize;
};

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_texCoord0;

layout (location = 0) out vec2 out_texCoord0;


void main() {
	gl_Position = vec4(in_pos / uni_viewportSize, 0.0, 1);
	out_texCoord0 = in_texCoord0;
}