#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <stdint.h>
#include <string>

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
			int32_t m_width;
			int32_t m_height;
			int32_t m_channels;

			friend class Renderer;

		public:
			Texture();
			Texture(const std::string& path);
			
			~Texture();

			void activateTexture(uint32_t slot);

			int32_t get() { return m_channels; }
		};
	} // namespace engine
} // namespace opengl

#endif // __TEXTURE_H__