#ifndef __WINDOW_WRAPPER__
#define __WINDOW_WRAPPER__

#include <stdint.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace opengl
{
	namespace engine
	{
		class Window
		{
		private:
			GLFWwindow* m_window = nullptr;
			uint32_t m_vertexBufferObject[2];
			uint32_t m_vertexArrayObject[2];
			uint32_t m_elementBufferObject;
			uint32_t m_shaderProgram_yellow;
			uint32_t m_shaderProgram_red;

		public:
			Window(uint32_t width, uint32_t height, const char* title);
			~Window();

		private:
			void setupGlfw();
			void setupVertex();

			void bufferSetup();
			void eboSetup();

			void run();
			void processInput();

			static void framebuffer_size_callback(GLFWwindow* win, int width, int height);
		};
	} // namespace engine
} // namespace opengl

#endif // __WINDOW_WRAPPER__