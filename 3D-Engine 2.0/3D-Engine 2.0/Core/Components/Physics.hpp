#ifndef Engine_Physics_hpp
#define Engine_Physics_hpp

#include <GLM/glm.hpp>

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Physics : public Component {
	public:
		Physics( float density = 1.0f, float restitution = 1.0f );
		virtual ~Physics( );

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

	private:
		glm::vec3 _acceleration;
		glm::vec3 _velocity;

		float _mass;
		float _density;
		float _restitution;
		float _momentum;
		float _angulatAcceleration;
		float _angularVelocity;

		bool _static;
	};
}

#endif
