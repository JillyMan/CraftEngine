#version 450 core

in vec3 FragPos;
in vec3 OutVertNormal;

layout (location = 0) out vec4 FragColor;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float AmbientStrength = 1.0f;

void main() {
	vec3 normal = normalize(OutVertNormal);
	vec3 lightDir = normalize(LightPosition - FragPos);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * LightColor;
	vec3 ambient = AmbientStrength * LightColor;
	FragColor = vec4((ambient + diffuse) * ObjectColor, 1.0f);
}
