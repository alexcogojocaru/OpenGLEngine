#include "Camera.h"

namespace opengl
{
	namespace engine
	{
		Camera::Camera(float windowWidth, float windowHeight)
			: windowWidth(windowWidth), windowHeight(windowHeight)
		{
			initMVP();
		}

		void Camera::initMVP()
		{
			view = glm::mat4(1.0f);
			projection = glm::mat4(1.0f);

			model = glm::scale(model, glm::vec3(0.2f, 0.9f, 0.2f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth / windowHeight), 0.1f, 100.0f);
		}
	}
}