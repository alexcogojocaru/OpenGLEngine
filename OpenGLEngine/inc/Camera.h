#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "graphics.h"

namespace opengl
{
	namespace engine
	{
		class Camera
		{
		private:
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;

			float windowWidth;
			float windowHeight;

		public:
			Camera(float windowWidth, float windowHeight);

			glm::mat4 getModel() const { return model; }
			glm::mat4 getView() const { return view; }
			glm::mat4 getProjection() const { return projection; }

		private:
			void initMVP();
		};

	} // namespace engine
} // namespace opengl

#endif // !__CAMERA_H__
