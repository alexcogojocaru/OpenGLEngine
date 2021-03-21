#include "Renderer.h"

using namespace opengl::engine;

int main()
{
	std::shared_ptr<Renderer> engine(Renderer::getRenderer());

	engine->setShape(new CubeMesh);
	engine->run();

	return 0;
}