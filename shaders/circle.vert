#version 330 core

layout (location = 0) in vec2 pos;

out vec2 fragPos;

uniform vec2 center;
uniform mat2 pl_Transform;


void main()
{
	gl_Position = vec4(pl_Transform * pos, 0, 1.0) + vec4(center, 0, 0);
	fragPos = pos;
}