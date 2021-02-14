#include "Renderer.h"

using namespace opengl::engine;

int main()
{
	Renderer* engine = Renderer::getRenderer();

	engine->startEngine();

	return 0;
}
