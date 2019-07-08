#include "crpch.h"
#include "OpenGLShader.h"

namespace Craft
{
	OpenGLShader::OpenGLShader(const char* vertexShader, const char* fragmentShader)
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

		ErrorCode(vertexShaderId, GL_COMPILE_STATUS);
		ErrorCode(fragmentShaderId, GL_COMPILE_STATUS);
		ErrorCode(m_ProgramId, GL_LINK_STATUS);

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramId);
	}

	void OpenGLShader::Use()
	{
		glUseProgram(m_ProgramId);
	}

	void OpenGLShader::Unuse()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform1i(const char* name, s32 value)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniform1f(const char* name, f32 value)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniform2f(const char* name, v2& value)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetUniform3f(const char* name, v3& value)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniform4f(const char* name, v4& value)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniformMatrix4fv(const char* name, mat4& mat)
	{
		GLint location = GetLocation(m_ProgramId, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, mat.e);
	}

	GLint OpenGLShader::GetLocation(GLuint program, const char* name)
	{
		GLint location = glGetUniformLocation(m_ProgramId, name);
		CR_ASSERT(location != -1, "Position not found");
		return location;
	}

	void OpenGLShader::ErrorCode(GLuint object, GLint status)
	{
		GLint success;
		GLchar info[512];

		switch (status)
		{
			case GL_COMPILE_STATUS:
			{
				glGetShaderiv(object, status, &success);
				if (!success)
				{
					glGetShaderInfoLog(object, 512, NULL, info);
					CR_WARN(info);
				}
				break;
			}
			case GL_LINK_STATUS:
			{
				glGetProgramiv(object, status, &success);
				if (!success)
				{
					glGetProgramInfoLog(object, 512, NULL, info);
					CR_WARN(info);
				}
				break;
			}
		}
	}
}