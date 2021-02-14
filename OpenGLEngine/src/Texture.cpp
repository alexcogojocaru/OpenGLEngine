#include "Texture.h"
#include "stb_image.h"
#include "Log.h"
#include "Shader.h"

namespace opengl
{
	namespace engine
	{
		Texture::Texture()
		{
		}

		void Texture::createTexture(Shader *shader)
		{
			int width;
			int height;
			int nrChannels;

			stbi_set_flip_vertically_on_load(true);

			glGenTextures(1, &m_glfwTextureWood);
			glBindTexture(GL_TEXTURE_2D, m_glfwTextureWood);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			uint8_t* data = stbi_load("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\textures\\wooden_container.jpg", &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				LOG_TRACE("wooden texture loaded successfully");
			}
			else
			{
				LOG_ERROR("wooden texture failed to load");
			}

			stbi_image_free(data);

			glGenTextures(1, &m_glfwTextureFace);
			glBindTexture(GL_TEXTURE_2D, m_glfwTextureFace);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			data = stbi_load("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\textures\\awesomeface.png", &width, &height, &nrChannels, 0);			
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				LOG_TRACE("face texture loaded successfully");
			}
			else
			{
				LOG_ERROR("face texture failed to load");
			}

			stbi_image_free(data);

			shader->useProgram();
			shader->setInt("texture1", 0);
			shader->setInt("texture2", 1);
		}

	} // namespace engine
} // namespace opengl