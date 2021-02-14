#include "..\inc\Shader.h"
#include "Log.h"

namespace opengl
{
	namespace engine
	{
		Shader::Shader()
		{
		}

		Shader::Shader(const char* vertexPath, const char* fragmentPath)
		{
			uint32_t vertex;
			uint32_t fragment;

			int success;

			std::string vertexStream = readData(vertexPath);
			std::string fragmentStream = readData(fragmentPath);

			const char* vertexCode = vertexStream.c_str();
			const char* fragmentCode = fragmentStream.c_str();

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vertexCode, nullptr);
			glCompileShader(vertex);
			checkShaderCompilation(vertex, "vertex");

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fragmentCode, nullptr);
			glCompileShader(fragment);
			checkShaderCompilation(fragment, "fragment");

			m_programID = glCreateProgram();
			glAttachShader(m_programID, vertex);
			glAttachShader(m_programID, fragment);
			glLinkProgram(m_programID);

			glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
			if (!success)
			{
				LOG_ERROR("shader program linking failed");
			}
			else
			{
				LOG_TRACE("shader program linking successfully");
			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_programID);
		}

		void Shader::useProgram()
		{
			glUseProgram(m_programID);
		}

		std::string Shader::readData(const char* path)
		{
			std::ifstream shaderFile;
			std::string shaderCode;

			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try 
			{
				shaderFile.open(path);

				std::stringstream shaderStream;
				shaderStream << shaderFile.rdbuf();
				shaderFile.close();
				shaderCode = shaderStream.str();
			}
			catch (std::ifstream::failure& e)
			{
				std::cerr << "CANNOT READ FILE" << std::endl;
			}

			return shaderCode;
		}
		
		void Shader::checkShaderCompilation(uint32_t shader, const char* type)
		{
			int success;

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				LOG_ERROR("[%s] compilation failed", type);
			}
			else
			{
				LOG_TRACE("[%s] compilation successfully", type);
			}

		}
	} // namespace engine
} // namespace opengl