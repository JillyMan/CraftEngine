#version 460

layout (location = 0) in vec3 Pos;

uniform mat4 ViewMatrix = mat4(1.0f);
uniform mat4 ModelMatrix = mat4(1.0f);
uniform mat4 ProjectionMatrix = mat4(1.0f);

uniform vec4 Color;
out vec4 FragColor;

void main() {
    FragColor = Color;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Pos, 1.0f);
}