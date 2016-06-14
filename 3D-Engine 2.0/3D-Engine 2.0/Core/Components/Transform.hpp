#ifndef Engine_Transformable_hpp
#define Engine_Transformable_hpp

#include <iostream>
#include <vector>
#include <memory>

#include <GLM/glm.hpp>
#include <GLM/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine
{
	class Transform : public Component
	{
	public:
		Transform(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
			: _position(pos), _rotation(glm::radians(rot)), _rotationQuat(glm::radians(rot)), _scale(scale) {};
		virtual ~Transform() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void SetPosition(glm::vec3 position);
		void SetPosition(GLfloat x, GLfloat y, GLfloat z);
		void Move(glm::vec3 move);
		void Move(GLfloat x, GLfloat y, GLfloat z);
		void SetPositionWithoutChildren(glm::vec3 position);
		void SetPositionWithoutChildren(GLfloat x, GLfloat y, GLfloat z);
		void MoveWithoutChildren(glm::vec3 move);
		void MoveWithoutChildren(GLfloat x, GLfloat y, GLfloat z);

		void SetRotation(glm::vec3 rotation);
		void SetRotation(GLfloat x, GLfloat y, GLfloat z);
		void Rotate(glm::vec3 rotate);
		void Rotate(GLfloat x, GLfloat y, GLfloat z);
		void SetRotationWithoutChildren(glm::vec3 rotation);
		void SetRotationWithoutChildren(GLfloat x, GLfloat y, GLfloat z);
		void RotateWithoutChildren(glm::vec3 rotate);
		void RotateWithoutChildren(GLfloat x, GLfloat y, GLfloat z);

		void Scale(GLfloat scale);
		void Scale(glm::vec3 scale);
		void Scale(GLfloat x, GLfloat y, GLfloat z);
		void ScaleWithoutChildren(GLfloat scale);
		void ScaleWithoutChildren(glm::vec3 scale);
		void ScaleWithoutChildren(GLfloat x, GLfloat y, GLfloat z);

		glm::vec3 GetPosition();

		glm::vec3 GetRotationCam();
		glm::vec3 GetRotationRad();
		glm::vec3 GetRotationDeg();
		glm::quat GetRotationQuat();

		glm::vec3 GetScale();

		glm::vec3 const & GetPositionRef();
		
		glm::vec3 const & GetRotationRadRef();
		glm::quat const & GetRotationQuatRef();

		glm::vec3 const & GetScaleRef();

	private:
		void MoveChildren(glm::vec3 move);

		void SetRotationChildren(glm::vec3 rotation);
		void RotateChildren(glm::vec3 rotate);

		void ScaleChildren(GLfloat scale);
		void ScaleChildren(glm::vec3 scale);

	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::quat _rotationQuat;
		glm::vec3 _scale;
	};
};
#endif

