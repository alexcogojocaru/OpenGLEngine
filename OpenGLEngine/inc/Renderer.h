#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Window.h"
#include "Shader.h"
#include "Texture.h"

constexpr auto windowWidth = 1280;
constexpr auto windowHeight = 720;
constexpr auto windowTitle = "OpenGL Engine";

namespace opengl
{
	namespace engine
	{
		class Window;
		class Shader;
		class Texture;

		class Renderer
		{
		private:
			static Renderer* engineInstance;

			Window m_window;
			Shader m_shader;
			Texture m_texture;

			uint32_t m_vertexBufferObject;
			uint32_t m_vertexArrayObject;
			uint32_t m_elementBufferObject;

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