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
		class Shader
		{
		private:
			uint32_t m_programID;

		public:
			Shader();
			Shader(const char* vertexPath, const char* fragmentPath);

			void useProgram();
			void deleteProgram();

			uint32_t getID() const { return m_programID; }

		private:
			std::string readData(const char *path);
			void checkShaderCompilation(uint32_t shader);
		};

	} // namespace engine
} // namespace opengl

#endif // __SHADER_H__