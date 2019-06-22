#version 460
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec4 vertexColour;

void main()
{
	vertexColour = colour;
	gl_Position = pos;
}