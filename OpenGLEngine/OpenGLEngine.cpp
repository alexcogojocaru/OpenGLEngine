#include "Renderer.h"

using namespace opengl::engine;

int main()
{
	std::shared_ptr<Renderer> engine(Renderer::getRenderer());

	engine->run();

	return 0;
}