#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <stdint.h>

#include "graphics.h"

namespace opengl
{
	namespace engine
	{
		class Renderer;
		class Shader;

		class Texture
		{
		private:
			uint32_t m_glfwTextureFace;
			uint32_t m_glfwTextureWood;

			Shader* m_shader = nullptr;

			friend class Renderer;
		public:
			Texture();

		private:
			void createTexture(Shader* shader);
		};
	} // namespace engine
} // namespace opengl

#endif // __TEXTURE_H__