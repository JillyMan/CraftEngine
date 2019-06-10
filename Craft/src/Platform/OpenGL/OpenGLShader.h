#pragma once

#include "OpenGL.h"
#include "Craft\Graphics\Shader.h"

namespace Craft
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader)
		{
			GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
			glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);

			glCompileShader(vertexShaderId);
			glCompileShader(fragmentShaderId);

#if CR_DEBUG
			IsCompileSuccess(vertexShaderId);
			IsCompileSuccess(fragmentShaderId);
#endif

			m_ProgramId = glCreateProgram();
			glAttachShader(m_ProgramId, vertexShaderId);
			glAttachShader(m_ProgramId, fragmentShaderId);
			glLinkProgram(m_ProgramId);

#if CR_DEBUG
			IsProgramLink(m_ProgramId);
#endif
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
		}

		~OpenGLShader()
		{
			glDeleteProgram(m_ProgramId);
		}

		void Use() override
		{
			glUseProgram(m_ProgramId);
		}

		void Unuse() override
		{
			glUseProgram(0);
		}

	private:

		void IsCompileSuccess(GLuint& shader)
		{
			GLint success;
			GLchar info[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, info);
				CR_WARN(info);
			}
		}

		void IsProgramLink(GLuint& program)
		{
			GLint success;
			GLchar info[512];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 512, NULL, info);
				CR_WARN(info);
			}
		}

		GLuint m_ProgramId;
	};
}