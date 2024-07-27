#version 460


layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_texCoord0;

layout (location = 0) out vec2 out_texCoord0;


void main() {
	gl_Position = vec4(in_pos, 1);
	out_texCoord0 = in_texCoord0;
}