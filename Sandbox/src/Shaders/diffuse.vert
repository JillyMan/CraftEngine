#version 460 core
layout(location = 0) in vec3 VertPosition;
layout(location = 1) in vec3 VertNormal;

out vec3 LightIntensity;

uniform vec3 Ld;
uniform vec3 Kd;
uniform vec4 LightPosition;

uniform mat4 ViewMatrix = mat4(1.0f);
uniform mat4 ModelMatrix = mat4(1.0f);
uniform mat4 ProjectionMatrix = mat4(1.0f);

mat3 mat3_emu(mat4 m4) {
	return mat3(
		m4[0][0], m4[0][1], m4[0][2],
		m4[1][0], m4[1][1], m4[1][2],
		m4[2][0], m4[2][1], m4[2][2]);
}

void main() {
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;	
	mat4 ModelViewProjection = ProjectionMatrix * ModelViewMatrix;

	mat3 NormalMatrix = mat3_emu(ModelViewMatrix);

	vec4 vertexInCameraSpace = ModelViewMatrix * vec4(VertPosition, 1.0f);
	vec3 s = normalize(vec3((ModelViewMatrix * LightPosition) - vertexInCameraSpace));
	vec3 n = normalize(NormalMatrix * VertNormal);
	LightIntensity = Ld * Kd * max(dot(s, n), 0.0f);

	gl_Position = ModelViewProjection * vec4(VertPosition, 1.0f);
}
