#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include <thread>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "meshes.h"

//#define WIREFRAME_MODE

#define DRAW_ELEMENTS
//#define DRAW_ARRAY

#define MODEL_MATRIX "u_model"
#define VIEW_MATRIX "u_view"
#define PROJECTION_MATRIX "u_projection"

namespace opengl
{
	namespace engine
	{
		constexpr auto windowWidth = 800;
		constexpr auto windowHeight = 600;
		constexpr auto windowTitle = "OpenGL Engine";

		constexpr auto vertexpath = "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\shaders\\vertex.vert";
		constexpr auto fragmentpath = "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\shaders\\fragment.frag";
		constexpr auto lightFragmentPath = "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\shaders\\light_fragment.frag";

		class Renderer
		{
		private:
			static std::shared_ptr<Renderer> engineInstance;

			Texture* m_texture1;
			Texture* m_texture2;

			Mesh* m_shape;

			Window m_window;
			std::shared_ptr<Shader> m_shader = nullptr;
			std::shared_ptr<Shader> m_lightShader = nullptr;
			std::shared_ptr<Camera> m_camera = nullptr;

			uint32_t m_vertex_array_object;
			uint32_t m_vertex_buffer_object;
			uint32_t m_index_buffer_object;

			uint32_t m_lightCubeVAO;

			glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

		private:
			Renderer();
		
			void createBuffers();

		public:
			~Renderer();

			static std::shared_ptr<Renderer> getRenderer();

			void run();
			void setShape(Mesh* shape) { m_shape = shape; };
		};

	} // namespace engine
} // namespace opengl

#endif // __RENDERER_H__