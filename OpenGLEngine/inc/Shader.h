#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define INFO_LOG_SIZE 512

namespace opengl
{
	namespace engine
	{
		class Texture;

		class Shader
		{
		private:
			uint32_t m_programID;

			friend class Texture;
		public:
			Shader();
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			void useProgram();

			uint32_t getID() const { return m_programID; }

			void setBool(const std::string& name, bool value) const
			{
				glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
			}

			void setInt(const std::string& name, int value) const
			{
				glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
			}

			void setFloat(const std::string& name, float value) const
			{
				glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
			}

		private:
			std::string readData(const char *path);
			void checkShaderCompilation(uint32_t shader, const char* type);
		};

	} // namespace engine
} // namespace opengl

#endif // __SHADER_H__