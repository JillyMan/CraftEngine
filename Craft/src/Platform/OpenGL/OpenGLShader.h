#pragma once

#include <Craft/Math/Vectors.h>
#include <Craft/Graphics/Core/Shader.h>

#include <Platform/OpenGL/OpenGL.h>

namespace Craft { namespace Graphics {

	class OpenGLShader : public Shader
	{
	private:
		GLuint m_ProgramId;

	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader);

		virtual ~OpenGLShader();

		virtual void Use() override;
		virtual void Unuse() override;

		virtual void SetUniform1i(const char* name, s32 value) override;

		virtual void SetUniform1f(const char* name, f32 value) override;
		virtual void SetUniform2f(const char* name, v2& value) override;
		virtual void SetUniform3f(const char* name, v3& value) override;
		virtual void SetUniform4f(const char* name, v4& value) override;
		virtual void SetUniformMatrix4fv(const char* name, mat4& mat) override;

	private:
		GLint GetLocation(GLuint program, const char* name);
		void ErrorCode(GLuint object, GLint status);
	};
}}