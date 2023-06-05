#version 330 core

uniform vec4 color;
uniform vec2 center;
/uniform int radius;

int vec2 fragPos;

out vec4 outColor;


void main()
{
	if (length(fragPos - center) > radius)
		discard;

	outColor = color;
}