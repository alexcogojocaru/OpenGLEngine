#include <iostream>
#include "Window.h"

namespace opengl
{
	namespace engine
	{
		float vertices[] = {
			 0.5f,  0.34f, 0.0f,  // top right
			 0.5f, -0.43f, 0.0f,  // bottom right
			-0.23f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.65f, 0.0f   // top left
		};

		uint32_t indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		float firstTriangle[] = {
			-0.9f, -0.5f, 0.0f,  // left 
			-0.0f, -0.5f, 0.0f,  // right
			-0.45f, 0.5f, 0.0f,  // top 
		};

		float secondTriangle[] = {
			0.5f, -0.5f, 0.0f,  // left
			0.9f, -0.5f, 0.0f,  // right
			0.45f, 0.5f, 0.0f   // top 
		};

		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"out vec4 vertexColor;\n"
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
			"}\0";

		const char* fragmentShaderSource_yellow =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(0.8f, 0.8f, 0.1f, 1.0f);\n"
			"}\0";

		const char* fragmentShaderSource_red =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 vertexColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vertexColor;\n"//vec4(0.9f, 0.0f, 0.1f, 1.0f);\n"
			"}\0";

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
			// bind the objects
			bufferSetup();
			eboSetup();

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// create vertex shader
			uint32_t vertexShader;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
			glCompileShader(vertexShader);

			int32_t success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// end of the vertex shader creation

			// create fragment shader
			uint32_t fragmentShaderYellow;
			fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSource_yellow, nullptr);
			glCompileShader(fragmentShaderYellow);

			glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragmentShaderYellow, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// end of the fragment shader creation

			// create shader program and attach the shaders
			m_shaderProgram_yellow = glCreateProgram();

			glAttachShader(m_shaderProgram_yellow, vertexShader);
			glAttachShader(m_shaderProgram_yellow, fragmentShaderYellow);
			glLinkProgram(m_shaderProgram_yellow);

			glGetShaderiv(m_shaderProgram_yellow, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_shaderProgram_yellow, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			// end of the shader program creation

			uint32_t fragmentShaderRed;

			fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderRed, 1, &fragmentShaderSource_red, nullptr);
			glCompileShader(fragmentShaderRed);

			m_shaderProgram_red = glCreateProgram();
			glAttachShader(m_shaderProgram_red, vertexShader);
			glAttachShader(m_shaderProgram_red, fragmentShaderRed);
			glLinkProgram(m_shaderProgram_red);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShaderYellow);
			glDeleteShader(fragmentShaderRed);
		}

		//void Window::vboSetup()
		//{
		//	glGenBuffers(2, m_vertexBufferObject);
		//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[0]);
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
		//}

		//void Window::vaoSetup()
		//{
		//	glGenVertexArrays(1, &m_vertexArrayObject);
		//	glBindVertexArray(m_vertexArrayObject);
		//}

		void Window::bufferSetup()
		{
			glGenVertexArrays(2, m_vertexArrayObject);
			glGenBuffers(2, m_vertexBufferObject);

			// first triangle
			glBindVertexArray(m_vertexArrayObject[0]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// second triangle
			glBindVertexArray(m_vertexArrayObject[1]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(0);
		}

		void Window::eboSetup()
		{
			glGenBuffers(1, &m_elementBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

				// drawing
				//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glUseProgram(m_shaderProgram_yellow);
				glBindVertexArray(m_vertexArrayObject[0]);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				glUseProgram(m_shaderProgram_red);
				glBindVertexArray(m_vertexArrayObject[1]);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				// events
				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}

			glDeleteVertexArrays(2, m_vertexArrayObject);
			glDeleteBuffers(2, m_vertexBufferObject);
			glDeleteProgram(m_shaderProgram_yellow);
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
