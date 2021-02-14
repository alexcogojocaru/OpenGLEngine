#include "Texture.h"
#include "../stb_image.h"
#include "Log.h"

namespace opengl
{
	namespace engine
	{
		Texture::Texture()
		{
		}

		void Texture::createTexture()
		{
			int width;
			int height;
			int nrChannels;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			uint8_t* data = stbi_load("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\textures\\wooden_container.jpg", &width, &height, &nrChannels, 0);

			glGenTextures(1, &m_glfwTexture);
			glBindTexture(GL_TEXTURE_2D, m_glfwTexture);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				LOG_TRACE("texture generated successfully");
			}
			else
			{
				LOG_ERROR("texture failed to generate");
			}
		}

	} // namespace engine
} // namespace opengl