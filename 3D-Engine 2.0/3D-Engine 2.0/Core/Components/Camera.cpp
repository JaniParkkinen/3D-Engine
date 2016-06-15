#include <Core/Components/Camera.hpp>

namespace Engine {
	Camera::Camera( glm::vec3 offset )
		: _offset( offset ) { };

	Camera::~Camera( ) { };

	void Camera::Init( ) {
		_ownerTransform = _owner->GetComponent<Transform>( );
	};

	void Camera::Cleanup( ) { };

	void Camera::Update( DeltaTime deltaTime ) { };

	glm::mat4 const Camera::GetViewMatrix( ) {
		return glm::lookAt( _ownerTransform->GetPosition( ) + _offset, _ownerTransform->GetPosition( ) + _ownerTransform->GetRotationCam( ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
	};

	glm::vec3 const Camera::GetPosition( ) {
		return _ownerTransform->GetPosition( );
	};
};