#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Window.h"
#include "Shader.h"
#include "Texture.h"

//#define WIREFRAME_MODE
#define POINT_COORDS 2 // 2 because we have (x, y) coords

namespace opengl
{
	namespace engine
	{
		constexpr auto windowWidth = 1280;
		constexpr auto windowHeight = 720;
		constexpr auto windowTitle = "OpenGL Engine";

		constexpr auto vertexpath = "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\shaders\\vertex.vert";
		constexpr auto fragmentpath = "D:\\Engine\\OpenGLEngine\\OpenGLEngine\\res\\shaders\\fragment.frag";

		class Renderer
		{
		private:
			static Renderer* engineInstance;
			static float positions[];
			static uint32_t indices[];

			Window m_window;
			Shader* m_shader = nullptr;
			Texture m_texture;

			uint32_t m_vertex_array_object;
			uint32_t m_vertex_buffer_object;
			uint32_t m_index_buffer_object;

		private:
			Renderer();
			~Renderer();

			void createBuffers();
		
		public:
			static Renderer* getRenderer();

			void startEngine();
		};

	} // namespace engine
} // namespace opengl

#endif // __RENDERER_H__