#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <stdint.h>

#include "graphics.h"

namespace opengl
{
	namespace engine
	{
		class Renderer;

		class Texture
		{
		private:
			uint32_t m_glfwTexture;

			friend class Renderer;
		public:
			Texture();

		private:
			void createTexture();
		};
	} // namespace engine
} // namespace opengl

#endif // __TEXTURE_H__