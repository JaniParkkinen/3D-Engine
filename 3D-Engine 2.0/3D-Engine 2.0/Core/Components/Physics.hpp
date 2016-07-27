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

		void SetAngularAcceleration( glm::vec3 acceleration );
		void AddAngularAcceleration( glm::vec3 acceleration );
		void SetAcceleration( glm::vec3 acceleration );
		void AddAcceleration( glm::vec3 acceleration );

		void SetAngularVelocity( glm::vec3 velocity );
		void AddAngularVelocity( glm::vec3 velocity );
		void SetVelocity( glm::vec3 velocity );
		void AddVelocity( glm::vec3 velocity );

		glm::vec3 GetAngularAcceleration( ) { return _angularAcceleration; }
		glm::vec3 GetAngularVelocity( ) { return _angularVelocity; }
		glm::vec3 GetAcceleration( ) { return _acceleration; }
		glm::vec3 GetVelocity( ) { return _velocity; }
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
