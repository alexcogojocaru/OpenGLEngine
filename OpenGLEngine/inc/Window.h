#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdint.h>

#include "graphics.h"

namespace opengl
{
	namespace engine
	{
		class Renderer;

		class Window
		{
		private:
			GLFWwindow* m_glfwWindow = nullptr;

			friend class Renderer;

		public:
			Window();
			Window(uint32_t width, uint32_t height, const char* title);

		private:
			void processInput();
			static void framebuffer_size_callback(GLFWwindow* win, int width, int height);
		};

	} // namespace engine
} // namespace opengl

#endif // __WINDOW_WRAPPER__