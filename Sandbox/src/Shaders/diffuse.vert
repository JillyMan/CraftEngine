#version 450 core
layout(location = 0) in vec3 VertPosition;
layout(location = 1) in vec3 VertNormal;

uniform mat4 ViewMatrix = mat4(1.0f);
uniform mat4 ModelMatrix = mat4(1.0f);
uniform mat4 ProjectionMatrix = mat4(1.0f);

out vec3 FragPos;
out vec3 OutVertNormal;

void main() {
	vec4 Vec4VertPos = vec4(VertPosition, 1.0f);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * Vec4VertPos;
	FragPos = (ModelMatrix * Vec4VertPos).xyz;

	//pls don't use inverse in gpu program, move to cpu
	OutVertNormal = mat3(transpose(inverse(ModelMatrix))) * VertNormal;
	//OutVertNormal = mat3(ModelMatrix) * VertNormal;
}