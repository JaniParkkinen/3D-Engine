#include <Core/Components/Physics.hpp>

namespace Engine {
	Physics::Physics( float mass, float restitution ) : _mass(mass), _restitution(restitution), Component( PHYS ) {

	}

	Physics::~Physics( ) {

	}

	void Physics::Init( ) {

	}

	void Physics::Cleanup( ) {

	}

	void Physics::Update( DeltaTime deltaTime ) {
		glm::vec3 newVelocity = _velocity + ( deltaTime * _acceleration );
		glm::vec3 newPosition = _position + ( deltaTime * newVelocity );
		float newAngularVelocity = _angularVelocity + ( deltaTime*_angularAcceleration );
		float newAngle = _angle + ( deltaTime * newAngularVelocity );

		setPosition( newPosition );
		setRotation( newRotation );
	}
}
