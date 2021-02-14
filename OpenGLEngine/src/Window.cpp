#include <iostream>
#include "Window.h"
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
				LOG_ERROR("Failed to create glfw window");
			}
			else
			{
				LOG_TRACE("glfw window created successfully");
			}

			glfwMakeContextCurrent(m_glfwWindow);
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
