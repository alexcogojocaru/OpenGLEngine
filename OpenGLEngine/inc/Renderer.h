#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include <thread>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"

//#define WIREFRAME_MODE

//#define DRAW_ELEMENTS
#define DRAW_ARRAY

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

		class Renderer
		{
		private:
			static std::shared_ptr<Renderer> engineInstance;
			static std::vector<float> positions;
			static std::vector<uint32_t> indices;

			Texture* m_texture1;
			Texture* m_texture2;

			Window m_window;
			std::shared_ptr<Shader> m_shader = nullptr;

			uint32_t m_vertex_array_object;
			uint32_t m_vertex_buffer_object;
			uint32_t m_index_buffer_object;

		private:
			Renderer();
		
			void createBuffers();
			static void startEngineCallback(Renderer* renderer);

		public:
			~Renderer();

			static std::shared_ptr<Renderer> getRenderer();

			void run();
			void startEngine();
		};

	} // namespace engine
} // namespace opengl

#endif // __RENDERER_H__