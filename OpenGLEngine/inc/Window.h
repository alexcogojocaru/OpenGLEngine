#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdint.h>

#include "graphics.h"
#include "Shader.h"

namespace opengl
{
	namespace engine
	{
		class Shader;

		class Window
		{
		private:
			Shader* shader = nullptr;

			GLFWwindow* m_window = nullptr;
			uint32_t m_vertexBufferObject;
			uint32_t m_vertexArrayObject;
			uint32_t m_elementBufferObject;

			uint32_t m_texture;

		public:
			Window(uint32_t width, uint32_t height, const char* title);
			~Window();

		private:
			void setupGlfw();
			void setupVertex();
			void setupTextures();

			void run();
			void processInput();

			static void framebuffer_size_callback(GLFWwindow* win, int width, int height);
		};

	} // namespace engine
} // namespace opengl

#endif // __WINDOW_WRAPPER__