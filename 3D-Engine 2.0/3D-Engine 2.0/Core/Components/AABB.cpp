#include <Core/Components/AABB.hpp>

namespace Engine {
	void AABB::Init() {
		_AABBIndiceData.push_back(glm::uvec3(0, 1, 2));
		_AABBIndiceData.push_back(glm::uvec3(2, 3, 0));
		_AABBIndiceData.push_back(glm::uvec3(0, 5, 6));
		_AABBIndiceData.push_back(glm::uvec3(1, 6, 7));
		_AABBIndiceData.push_back(glm::uvec3(2, 7, 4));
		_AABBIndiceData.push_back(glm::uvec3(3, 4, 5));
	};

	void AABB::Cleanup() {};

	void AABB::Update(DeltaTime deltaTime) {};

	void AABB::UpdateAABB(glm::vec3 min, glm::vec3 max) {
		_min = min;
		_max = max;

		_AABBVetrexData.clear();

		_AABBVetrexData.push_back(glm::vec3(max.x, max.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, min.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, min.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, max.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, max.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, max.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, min.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, min.y, min.z));
	};
};