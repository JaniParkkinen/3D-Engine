#ifndef Engine_Physics_hpp
#define Engine_Physics_hpp

#include <GLM/glm.hpp>

#include <Core/Time.hpp>

#include <Core/Managers/EntityManager.hpp>
#include <Core/Components/Transform.hpp>

namespace Engine {

	class Physics : public Component {
	public:
		Physics( float density = 1.0f, bool isStatic = false, float restitution = 1.0f );
		virtual ~Physics( );

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		void Update( DeltaTime deltaTime );
	private:
		glm::vec3 _acceleration;
		glm::vec3 _velocity;
		glm::vec3 _angularAcceleration;
		glm::vec3 _angularVelocity;

		float _mass;
		float _density;
		float _restitution;
		float _momentum;

		bool _static;
	};
}

#endif
