#include <vector>
#include "Renderer.h"
#include "Log.h"
#include "PyramidMesh.h"

namespace opengl
{
	namespace engine
	{
		PyramidMesh pyramid;

		std::shared_ptr<Renderer> Renderer::engineInstance = nullptr;

		//std::vector<float> Renderer::positions = {
		//	 0.5f,  0.5f, 0.0f,  
		//	 0.5f, -0.5f, 0.0f,  
		//	-0.5f, -0.5f, 0.0f,  
		//	-0.5f,  0.5f, 0.0f   
		//};

		std::vector<float> Renderer::positions = {
			  

		/*-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 

		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 

		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f*/
		};

		std::vector<uint32_t> Renderer::indices = {
			0, 1, 2, // first base
			0, 2, 3, // second base,
			0, 1, 4, // first face
			1, 2, 4, // second face
			2, 3, 4, // third face
			3, 0, 4  // fourth face
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
				LOG_ERROR("Failed to initialize glad");
			}

			glEnable(GL_DEPTH_TEST);

			m_shader = std::make_shared<Shader>(vertexpath, fragmentpath);

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

			createBuffers();
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
			glBufferData(GL_ARRAY_BUFFER, pyramid.points.size() * sizeof(glm::vec3), pyramid.points.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramid.indices.size() * sizeof(glm::ivec3), pyramid.indices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Renderer::run()
		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 rotation = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			m_shader->useProgram();

			//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			model = glm::rotate(model, glm::radians(22.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			
			view = glm::translate(view, glm::vec3(0.0f, -0.5f, 0.0f));
			//projection = glm::perspective(glm::radians(-75.0f), static_cast<float>(windowWidth / windowHeight), 0.1f, 100.0f);

			m_shader->setMatrix4x4("model", model);
			m_shader->setMatrix4x4("view", view);
			m_shader->setMatrix4x4("projection", projection);

			while (!glfwWindowShouldClose(m_window.m_glfwWindow))
			{
				m_window.processInput();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glBindVertexArray(m_vertex_array_object);
				
				#if defined(DRAW_ELEMENTS)
					glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
				#elif defined(DRAW_ARRAY)
					glDrawArrays(GL_TRIANGLES, 0, positions.size());
				#endif
				
					glfwSwapBuffers(m_window.m_glfwWindow);
				glfwPollEvents();
			}
		}

	} // namespace engine
} // namespace opengl