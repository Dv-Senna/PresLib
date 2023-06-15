#version 330 core

layout (location = 0) in vec2 pos;

uniform mat2 pl_Transform;
uniform vec2 upos;


void main()
{
	gl_Position = vec4(pl_Transform * pos + upos, 0.0, 1.0);
}