#ifndef Camera_hpp
#define Camera_hpp

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>
#include <Core/Components/Transform.hpp>

namespace Engine
{
	class Camera : public Component
	{
	public:
		Camera(glm::vec3 offset = glm::vec3(0.0f));
		virtual ~Camera();

		virtual void Init();
		virtual void Cleanup();

		virtual void Update(DeltaTime deltaTime);

		glm::mat4 const GetViewMatrix();
		glm::vec3 const GetPosition();
	private:
		std::shared_ptr<Transform> _ownerTransform;
		glm::vec3 _offset;
	};
};
#endif
