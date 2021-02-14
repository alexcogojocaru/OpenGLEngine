#include <iostream>
#include "Window.h"
#include "../stb_image.h"
#include "Log.h"

namespace opengl
{
	namespace engine
	{

		float vertices[] = {
			//positions				// colors				// tex coords
			0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,	  // top right
			0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f    // top left 
		};

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		Window::Window(uint32_t width, uint32_t height, const char* title)
		{
			setupGlfw();

			m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
			if (!m_window)
			{
				std::cerr << "Failed to create glfw window" << std::endl;
			}

			glfwMakeContextCurrent(m_window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to initialize glad" << std::endl;
			}

			glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

#ifdef WIREFRAME_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
			setupVertex();
			setupTextures();

			shader = new Shader("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\shaders\\vertex.vert", "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\shaders\\fragment.frag");

			run();
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::setupGlfw()
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void Window::setupVertex()
		{
			glGenVertexArrays(1, &m_vertexArrayObject);
			glGenBuffers(1, &m_vertexBufferObject);
			glGenBuffers(1, &m_elementBufferObject);

			glBindVertexArray(m_vertexArrayObject);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Window::setupTextures()
		{
			int width;
			int height;
			int nrChannels;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			uint8_t* data = stbi_load("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\textures\\wooden_container.jpg", &width, &height, &nrChannels, 0);

			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				LOG_TRACE("texture generated successfully");
			}
			else
			{
				LOG_ERROR("texture failed to generate");
			}
		}

		void Window::run()
		{
			while (!glfwWindowShouldClose(m_window))
			{
				// input
				processInput();

				// rendering
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glBindTexture(GL_TEXTURE_2D, m_texture);

				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
				transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

				// drawing
				shader->useProgram();
				uint32_t transformLoc = glGetUniformLocation(shader->getID(), "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

				glBindVertexArray(m_vertexArrayObject);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				// events
				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}

			glDeleteVertexArrays(1, &m_vertexArrayObject);
			glDeleteBuffers(1, &m_vertexBufferObject);
			glDeleteBuffers(1, &m_elementBufferObject);
		}

		void Window::processInput()
		{
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(m_window, true);
			}
		}

		void Window::framebuffer_size_callback(GLFWwindow* win, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

	} // namespace engine
} // namespace opengl
