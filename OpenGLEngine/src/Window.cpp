#include <iostream>
#include "Window.h"
#include "../stb_image.h"
#include "Log.h"

namespace opengl
{
	namespace engine
	{
		Window::Window()
		{
		}

		Window::Window(uint32_t width, uint32_t height, const char* title)
		{
			m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
			if (!m_glfwWindow)
			{
				std::cerr << "Failed to create glfw window" << std::endl;
			}

			glfwMakeContextCurrent(m_glfwWindow);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to initialize glad" << std::endl;
			}

			glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);
		}

		void Window::processInput()
		{
			if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(m_glfwWindow, true);
			}
		}

		void Window::framebuffer_size_callback(GLFWwindow* win, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

	} // namespace engine
} // namespace opengl
