#ifndef Engine_PhysicsSystem_hpp
#define Engine_PhysicsSystem_hpp

#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Buffer.hpp>

#include <Core/Managers/SystemManager.hpp>

#include <Core/Components/Transform.hpp>
#include <Core/Components/Renderable.hpp>
#include <Core/Components/AABB.hpp>

namespace Engine {
	class PhysicsSystem : public System {
	public:
		PhysicsSystem( ) : System( ) { };
		virtual ~PhysicsSystem( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		virtual void Pause( ) override;
		virtual void Resume( ) override;

		virtual void Update( DeltaTime deltaTime ) override;

		bool CheckAABBCollision( std::shared_ptr<Entity> lhsEntity, std::shared_ptr<Entity> rhsEntity );
	private:
		EntityManager* _entityManager;
	};
};
#endif
