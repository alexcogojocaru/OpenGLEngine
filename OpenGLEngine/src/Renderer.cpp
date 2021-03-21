#include <vector>
#include "Renderer.h"
#include "Log.h"
#include "PyramidMesh.h"

namespace opengl
{
	namespace engine
	{
		std::shared_ptr<Renderer> Renderer::engineInstance = nullptr;

		Renderer::Renderer()
			: m_shape(nullptr)
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
				LOG_ERROR("Failed to initialize glad");
			}

			glEnable(GL_DEPTH_TEST);

			m_shader = std::make_shared<Shader>(vertexpath, fragmentpath);
			m_lightShader = std::make_shared<Shader>(vertexpath, lightFragmentPath);
			m_camera = std::make_shared<Camera>(windowWidth, windowHeight);

			m_shader->useProgram();

			m_texture1 = new Texture("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\textures\\wooden_container.jpg");
			m_texture2 = new Texture("D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\textures\\awesomeface.png");

			/*m_texture1->activateTexture(0);
			m_texture2->activateTexture(1);*/

			/*m_shader->setInt("u_texture1", 0);
			m_shader->setInt("u_texture2", 1);*/

#ifdef WIREFRAME_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
		}

		Renderer::~Renderer()
		{
			glDeleteVertexArrays(1, &m_vertex_array_object);
			glDeleteBuffers(1, &m_vertex_buffer_object);

			glfwTerminate();
		}

		std::shared_ptr<Renderer> Renderer::getRenderer()
		{
			if (engineInstance == nullptr)
			{
				engineInstance = std::shared_ptr<Renderer>(new Renderer());
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
			glBufferData(GL_ARRAY_BUFFER, m_shape->points.size() * sizeof(glm::vec3), m_shape->points.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_shape->indices.size() * sizeof(glm::ivec3), m_shape->indices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glGenVertexArrays(1, &m_lightCubeVAO);
			glBindVertexArray(m_lightCubeVAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		void Renderer::run()
		{
			if (m_shape == nullptr)
			{
				LOG_EXCEPTION("Shape mesh is not initialized");
				return;
			}

			createBuffers();

			m_shader->setMatrix4x4("view", m_camera->getView());
			m_shader->setMatrix4x4("projection", m_camera->getProjection());

			while (!glfwWindowShouldClose(m_window.m_glfwWindow))
			{
				m_window.processInput();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_shader->useProgram();
				m_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
				m_shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

				glm::mat4 model = glm::mat4(1.0f);

				model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
				m_shader->setMatrix4x4("model", model);

				glBindVertexArray(m_vertex_array_object);

				{
				#if defined(DRAW_ELEMENTS)
					glDrawElements(GL_TRIANGLES, m_shape->indices.size() * 3, GL_UNSIGNED_INT, 0);
				#elif defined(DRAW_ARRAY)
					glDrawArrays(GL_TRIANGLES, 0, positions.size());
				#endif
				}

				/*m_lightShader->useProgram();
				m_lightShader->setMatrix4x4("projection", m_camera->getProjection());
				m_lightShader->setMatrix4x4("view", m_camera->getView());
				model = glm::translate(model, lightPos);
				m_lightShader->setMatrix4x4("model", model);

				glBindVertexArray(m_lightCubeVAO);
				glDrawElements(GL_TRIANGLES, m_shape->indices.size() * 3, GL_UNSIGNED_INT, 0);*/

				glfwSwapBuffers(m_window.m_glfwWindow);
				glfwPollEvents();
			}
		}

	} // namespace engine
} // namespace opengl