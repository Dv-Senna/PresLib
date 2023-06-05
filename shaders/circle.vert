#version 330 core

layout (location = 0) in vec2 pos;

out vec2 fragPos;


void main()
{
	gl_Position = vec4(pos, 1.0);
	fragPos = pos;
}