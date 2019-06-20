#pragma once

#include "OpenGL.h"
#include "Craft\Graphics\Shader.h"

namespace Craft
{
	class CRAFT_API OpenGLShader : public Shader
	{
	private:
		GLuint m_ProgramId;

	private:
		void ErrorCode(GLuint object, GLint status)
		{
			GLint success;
			GLchar info[512];

			if (status == GL_COMPILE_STATUS)
			{
				glGetShaderiv(object, status, &success);
				glGetShaderInfoLog(object, 512, NULL, info);
			}
			else if(status == GL_LINK_STATUS)
			{
				glGetProgramiv(object, status, &success);
				glGetProgramInfoLog(object, 512, NULL, info);
			}

			if (!success)
			{
				CR_WARN(info);
			}
		}

	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader)
		{
			GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
			glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);

			glCompileShader(vertexShaderId);
			glCompileShader(fragmentShaderId);

			m_ProgramId = glCreateProgram();
			glAttachShader(m_ProgramId, vertexShaderId);
			glAttachShader(m_ProgramId, fragmentShaderId);
			glLinkProgram(m_ProgramId);
			glValidateProgram(m_ProgramId);

			ErrorCode(m_ProgramId, GL_LINK_STATUS);
			ErrorCode(vertexShaderId, GL_COMPILE_STATUS);
			ErrorCode(fragmentShaderId, GL_COMPILE_STATUS);

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
	};
}