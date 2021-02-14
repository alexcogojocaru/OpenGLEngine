#include <vector>
#include "Renderer.h"
#include "Log.h"

namespace opengl
{
	namespace engine
	{
		Renderer* Renderer::engineInstance = nullptr;

		float Renderer::positions[] = {
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
			-0.5f, -0.5f,
		};

		uint32_t Renderer::indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Renderer::Renderer()
		{
			LOG_TRACE("render engine started");

			// first initialize the glfw to be able to use opengl
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_window = Window(windowWidth, windowHeight, windowTitle);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to initialize glad" << std::endl;
			}

			m_shader = new Shader(vertexpath, fragmentpath);
			//m_texture.createTexture(&m_shader);

#ifdef WIREFRAME_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

			createBuffers();
		}

		Renderer::~Renderer()
		{
			glDeleteVertexArrays(1, &m_vertex_array_object);
			glDeleteBuffers(1, &m_vertex_buffer_object);

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

		void Renderer::createBuffers()
		{
			glGenVertexArrays(1, &m_vertex_array_object);
			glGenBuffers(1, &m_vertex_buffer_object);
			glGenBuffers(1, &m_index_buffer_object);
			glBindVertexArray(m_vertex_array_object);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);
		}

		void Renderer::startEngine()
		{
			m_shader->useProgram();

			int32_t uColorLocation = glGetUniformLocation(m_shader->getID(), "u_color");
			if (uColorLocation != -1)
			{
				glUniform4f(uColorLocation, 0.2f, 0.3f, 0.8f, 1.0f);
			}
			else
			{
				LOG_ERROR("could not find uniform location");
			}

			glBindVertexArray(m_vertex_array_object);

			while (!glfwWindowShouldClose(m_window.m_glfwWindow))
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr);

				glfwSwapBuffers(m_window.m_glfwWindow);
				glfwPollEvents();
			}
		}

	} // namespace engine
} // namespace opengl