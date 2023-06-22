#version 330 core

uniform vec4 color;
uniform vec2 center;
uniform float radius;

in vec2 fragPos;

out vec4 outColor;


void main()
{
	if (length(fragPos - center) > radius)
	{
		outColor = vec4(0, 0, 0, 0);
		return;
	}

	outColor = color;
}