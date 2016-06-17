#ifndef Engine_AABB_hpp
#define Engine_AABB_hpp

#include <GLM/glm.hpp>

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class AxisAlignedBoundingBox : public Component {
	public:
		friend class PhysicsSystem;

		AxisAlignedBoundingBox( ) { };
		virtual ~AxisAlignedBoundingBox( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		void UpdateAABB( glm::vec3 min, glm::vec3 max );

		std::vector<glm::vec3> GetVertexData( ) { return _AABBVetrexData; };
		std::vector<glm::uvec3> GetIndiceData( ) { return _AABBIndiceData; };
	private:
		std::vector<glm::vec3> _AABBVetrexData;
		std::vector<glm::uvec3> _AABBIndiceData;

		glm::vec3 _min;
		glm::vec3 _max;
	};
};

#endif