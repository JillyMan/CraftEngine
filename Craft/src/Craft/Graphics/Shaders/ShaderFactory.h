#pragma once

namespace Craft { namespace Graphics {

	const char* ANGLE_STRING = "angle";
	const char* TEXTURE_STRING = "texture";
	const char* MIX_COEFFICIENT_STRING = "mixCoefficient";
	const char* U_COLOR_STRING = "u_color";

	const char* VIEW_MATRIX_STRING = "vw_matrix";
	const char* MODEL_MATRIX_STRING = "ml_matrix";
	const char* PROJECTION_MATRIX_STRING = "pr_matrix";

	const char* GetVertexWithTextureShader()
	{
		return
			R"(
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 InTexCoord1;
//layout (location = 2) in vec2 InTexCoord2;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out vec2 TexCoord1;
//out vec2 TexCoord2;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(pos, 1.0f);

	TexCoord1 = InTexCoord1;
	//TexCoord2 = InTexCoord2;
})";
	}

	const char* GetFragmentWithTextureShader()
	{
		return
			R"(
#version 460 core

uniform float mixCoefficient = 0.5f;
uniform sampler2D texture0;
//uniform sampler2D texture1;
uniform vec4 u_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

in vec2 TexCoord1;
//in vec2 TexCoord2;
out vec4 color;

void main()
{
	color = u_color * texture(texture0, TexCoord1);
})";
	}

	const char* GetSimpleVertexShader()
	{
		return R"(
#version 460 core
layout (location = 0) in vec3 pos;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

void main() {
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(pos, 1.0f);
})";
	}

	const char* GetFragmentColorShader() {
		return R"(
#version 460 core

uniform vec3 u_color;

out vec4 color;

void main() {
	color = vec4(u_color, 1.0f);
})";
	}
} }