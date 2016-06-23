#include <Core/Components/Physics.hpp>

namespace Engine {
	Physics::Physics( float mass, bool isStatic, float restitution )
		: _mass( mass )
		, _static( isStatic )
		, _density( 0.0f )
		, _restitution( restitution )
		, _momentum( 0.0f )
		, _acceleration( glm::vec3( 0.0f ) )
		, _velocity( glm::vec3( 0.0f, 0.0f, 0.0f ) )
		, _angularAcceleration( glm::vec3( 0.0f, 0.0f, 0.0f ) )
		, _angularVelocity( glm::vec3( 0.0f ) )
		, Component( PHYS ) {

	}

	Physics::~Physics( ) {

	}

	void Physics::Init( ) {

	}

	void Physics::Cleanup( ) {

	}

	void Physics::Update( DeltaTime deltaTime ) {
		if ( ( _owner->GetKey( ) & TRANSFORM ) == TRANSFORM ) {
			std::shared_ptr<Engine::Transform> transform = _owner->GetComponent<Engine::Transform>( TRANSFORM );

			glm::vec3 newVelocity = _velocity + ( ( float )deltaTime * _acceleration );
			glm::vec3 newPosition = transform->GetPosition( ) + ( ( float )deltaTime * newVelocity );
			glm::vec3 newAngularVelocity = _angularVelocity + ( ( float )deltaTime*_angularAcceleration );
			glm::vec3 newRotation = transform->GetRotationRad( ) + ( ( float )deltaTime * newAngularVelocity );

			transform->SetPosition( newPosition );
			transform->SetRotation( newRotation );

			_velocity = newVelocity;
			_angularVelocity = newAngularVelocity;
		}
	}

	void Physics::SetAngularAcceleration( glm::vec3 acceleration ) {
		_angularAcceleration = acceleration;
	}

	void Physics::AddAngularAcceleration( glm::vec3 acceleration ) {
		_angularAcceleration += acceleration;
	}

	void Physics::SetAcceleration( glm::vec3 acceleration ) {
		_acceleration = acceleration;
	}

	void Physics::AddAcceleration( glm::vec3 acceleration ) {
		_acceleration += acceleration;
	}

	void Physics::SetAngularVelocity( glm::vec3 velocity ) {
		_angularVelocity = velocity;
	}

	void Physics::AddAngularVelocity( glm::vec3 velocity ) {
		_angularVelocity += velocity;
	}

	void Physics::SetVelocity( glm::vec3 velocity ) {
		_velocity = velocity;
	}

	void Physics::AddVelocity( glm::vec3 velocity ) {
		_velocity += velocity;
	}
}
