#include "Renderer.h"
#include "..\inc\Renderer.h"

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

		Renderer* Renderer::engineInstance = nullptr;

		Renderer::Renderer()
		{
			// first initialize the glfw to be able to use opengl
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_window = Window(windowWidth, windowHeight, windowTitle);
			m_shader = Shader("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\shaders\\vertex.vert", "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\shaders\\fragment.frag");
			m_texture.createTexture();

#ifdef WIREFRAME_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

			createBuffers();
		}

		Renderer::~Renderer()
		{
			glDeleteVertexArrays(1, &m_vertexArrayObject);
			glDeleteBuffers(1, &m_vertexBufferObject);
			glDeleteBuffers(1, &m_elementBufferObject);

			glfwTerminate();
		}

		Renderer* Renderer::getRenderer()
		{
			if (engineInstance == nullptr)
			{
				engineInstance = new Renderer();
			}

			return engineInstance;
		}

		void Renderer::startEngine()
		{
			while (!glfwWindowShouldClose(m_window.m_glfwWindow))
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glBindTexture(GL_TEXTURE_2D, m_texture.m_glfwTexture);

				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
				transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

				m_shader.useProgram();
				uint32_t transformLoc = glGetUniformLocation(m_shader.getID(), "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

				glBindVertexArray(m_vertexArrayObject);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				// events
				glfwSwapBuffers(m_window.m_glfwWindow);
				glfwPollEvents();
			}
		}

		void Renderer::createBuffers()
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

	} // namespace engine
} // namespace opengl