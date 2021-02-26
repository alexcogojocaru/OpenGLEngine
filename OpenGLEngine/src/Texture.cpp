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

		Texture::Texture(const std::string& path)
		{
			stbi_set_flip_vertically_on_load(true);

			glGenTextures(1, &m_glfwTexture);
			glBindTexture(GL_TEXTURE_2D, m_glfwTexture);
		
			stbi_uc* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				stbi_image_free(data);
			}
			else
			{
				LOG_ERROR("failed to load the texture");
			}
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_glfwTexture);
		}

		void Texture::activateTexture(uint32_t slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_glfwTexture);
		}

	} // namespace engine
} // namespace opengl