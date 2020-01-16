#include "crpch.h"

#include "OpenGLShader.h"

namespace Craft { namespace Graphics {
        
        static GLenum MapFromShaderTypeToGLShaderType(ShaderType type) {
            switch (type) {
                case ShaderType::Vertex: return GL_VERTEX_SHADER;
                case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
                case ShaderType::Geometry: return GL_GEOMETRY_SHADER;
                default:
                CR_CORE_WARN("Invalid shader type..");
            }
        }

        OpenGLShader::OpenGLShader()
        {
            m_ProgramId = glCreateProgram();

			if (!m_ProgramId) {
                CR_CORE_ERROR("Can't create shader program");
            }
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
        
        void OpenGLShader::Link() {
            glLinkProgram(m_ProgramId);
			ValidataProgram();
        }
        
        void OpenGLShader::AttachShader(const char* shaderSource, ShaderType shaderType) {
            GLuint shaderId = glCreateShader(MapFromShaderTypeToGLShaderType(shaderType));
            glShaderSource(shaderId, 1, &shaderSource, NULL);
            glCompileShader(shaderId);

			if (ValidateShader(shaderId) == GL_TRUE) {
				glAttachShader(m_ProgramId, shaderId);
				//shader will be deleted only after Detach from shader-program
				glDeleteShader(shaderId);
			}
        }

		GLboolean OpenGLShader::ValidateShader(GLint shaderId) {
			GLint success;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
			
			if (success == GL_FALSE) {
				s32 length = 0;
				String logString;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

				if (length > 0) {
					GLchar* cLog = new GLchar[length];
					glGetShaderInfoLog(shaderId, length, NULL, cLog);
					logString = String(cLog);
					delete[] cLog;

				}

				String msg = "An error occurred in shader compilation: " + logString;
				CR_CORE_ERROR(msg);
		
				return GL_FALSE;
			}

			return GL_TRUE;
		}

		GLboolean OpenGLShader::ValidataProgram() {
			glValidateProgram(m_ProgramId);

			GLint success;
			glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);

			if (success == GL_FALSE) {
				s32 length = 0;
				String logString;
				glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &length);
				
				if (length > 0) {
					GLchar* cLog = new GLchar[length];
					glGetProgramInfoLog(m_ProgramId, length, NULL, cLog);
					logString = String(cLog);
					delete[] cLog;
				}

				String msg = "An error occured in when program has been link" + logString;
				CR_CORE_ERROR(msg);

				return true;
			}

			return true;
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
            auto pos = m_UniformLocations.find(name);
            if (pos == m_UniformLocations.end()) {
                GLint location = glGetUniformLocation(m_ProgramId, name);
                CR_ASSERT(location != -1, "Position not found");
                m_UniformLocations[name] = location;
            }
            return m_UniformLocations[name];
        }
    } }
