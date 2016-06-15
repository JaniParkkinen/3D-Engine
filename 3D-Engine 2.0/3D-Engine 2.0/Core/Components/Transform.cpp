#include <Core/Components/Transform.hpp>

namespace Engine {
	void Transform::Init( ) { }

	void Transform::Cleanup( ) { }

	void Transform::Update( DeltaTime deltaTime ) { }

	///-----------------------------------------------------

	void Transform::SetPosition( glm::vec3 position ) {
		glm::vec3 offset = _position - position;
		_position = position;
		this->MoveChildren( offset );
	};

	void Transform::SetPosition( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 position = glm::vec3( x, y, z );
		glm::vec3 offset = _position - position;
		_position = position;
		this->MoveChildren( offset );
	};

	void Transform::Move( glm::vec3 move ) {
		_position += move;
		this->MoveChildren( move );
	};

	void Transform::Move( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 move = glm::vec3( x, y, z );
		_position += move;
		this->MoveChildren( move );
	};

	void Transform::SetPositionWithoutChildren( glm::vec3 position ) {
		_position = position;
	};

	void Transform::SetPositionWithoutChildren( GLfloat x, GLfloat y, GLfloat z ) {
		_position = glm::vec3( x, y, z );
	};

	void Transform::MoveWithoutChildren( glm::vec3 move ) {
		_position += move;
	};

	void Transform::MoveWithoutChildren( GLfloat x, GLfloat y, GLfloat z ) {
		_position += glm::vec3( x, y, z );
	};

	///-----------------------------------------------------

	void Transform::SetRotation( glm::vec3 rotation ) {
		_rotationQuat = glm::quat( glm::radians( rotation ) );
		_rotation = glm::radians( rotation );
		this->SetRotationChildren( rotation );
	};

	void Transform::SetRotation( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 rotation = glm::vec3( x, y, z );
		_rotationQuat = glm::quat( glm::radians( rotation ) );
		_rotation = glm::radians( rotation );
		this->SetRotationChildren( rotation );
	};

	void Transform::Rotate( glm::vec3 rotate ) {
		_rotationQuat *= glm::quat( glm::radians( rotate ) );
		_rotation += glm::radians( rotate );
		this->RotateChildren( rotate );
	};

	void Transform::Rotate( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 rotate = glm::vec3( x, y, z );
		_rotationQuat *= glm::quat( glm::radians( rotate ) );
		_rotation += glm::radians( rotate );
		this->RotateChildren( rotate );
	};

	void Transform::SetRotationWithoutChildren( glm::vec3 rotation ) {
		_rotationQuat = glm::quat( glm::radians( rotation ) );
		_rotation = glm::radians( rotation );
	};

	void Transform::SetRotationWithoutChildren( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 rotation = glm::vec3( x, y, z );
		_rotationQuat = glm::quat( glm::radians( rotation ) );
		_rotation = glm::radians( rotation );
	};

	void Transform::RotateWithoutChildren( glm::vec3 rotate ) {
		_rotationQuat *= glm::quat( glm::radians( rotate ) );
		_rotation += glm::radians( rotate );
	};

	void Transform::RotateWithoutChildren( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 rotate = glm::vec3( x, y, z );
		_rotationQuat *= glm::quat( glm::radians( rotate ) );
		_rotation += glm::radians( rotate );
	};

	///-----------------------------------------------------

	void Transform::Scale( GLfloat scale ) {
		_scale *= glm::vec3( scale );
		this->ScaleChildren( scale );
	};

	void Transform::Scale( glm::vec3 scale ) {
		_scale *= scale;
		this->ScaleChildren( scale );
	};

	void Transform::Scale( GLfloat x, GLfloat y, GLfloat z ) {
		glm::vec3 scale = glm::vec3( x, y, z );
		_scale *= scale;
		this->ScaleChildren( scale );
	};

	void Transform::ScaleWithoutChildren( GLfloat scale ) {
		_scale *= glm::vec3( scale );
	};

	void Transform::ScaleWithoutChildren( glm::vec3 scale ) {
		_scale *= scale;
	};

	void Transform::ScaleWithoutChildren( GLfloat x, GLfloat y, GLfloat z ) {
		_scale *= glm::vec3( x, y, z );
	};

	///-----------------------------------------------------

	glm::vec3 Transform::GetPosition( ) { return _position; };
	glm::vec3 Transform::GetRotationCam( ) { return glm::degrees( glm::vec3( cos( _rotation.x ), tan( _rotation.y ), sin( _rotation.x ) ) ); };
	glm::vec3 Transform::GetRotationRad( ) { return _rotation; };
	glm::vec3 Transform::GetRotationDeg( ) { return glm::degrees( _rotation ); };
	glm::quat Transform::GetRotationQuat( ) { return _rotationQuat; }
	glm::vec3 Transform::GetScale( ) { return _scale; };

	glm::vec3 const & Transform::GetPositionRef( ) { return _position; };
	glm::vec3 const & Transform::GetRotationRadRef( ) { return _rotation; };
	glm::quat const & Transform::GetRotationQuatRef( ) { return _rotationQuat; }
	glm::vec3 const & Transform::GetScaleRef( ) { return _scale; };

	///-----------------------------------------------------

	void Transform::MoveChildren( glm::vec3 move ) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren( );
		for ( std::shared_ptr<Entity> child : children ) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>( );
			if ( childTransform != nullptr ) {
				childTransform->Move( move );
			};
		};
	};

	///-----------------------------------------------------

	void Transform::SetRotationChildren( glm::vec3 rotation ) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren( );
		for ( std::shared_ptr<Entity> child : children ) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>( );
			if ( childTransform != nullptr ) {

				//KORJATAAN!!!
				glm::quat rot = glm::quat( this->GetRotationRad( ) - childTransform->GetRotationRad( ) );

				childTransform->SetPosition( this->GetPosition( ) + ( rot * ( childTransform->GetPosition( ) - this->GetPosition( ) ) ) );

				childTransform->SetRotation( rotation );
			};
		};
	};

	void Transform::RotateChildren( glm::vec3 rotate ) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren( );
		for ( std::shared_ptr<Entity> child : children ) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>( );
			if ( childTransform != nullptr ) {

				//KORJATAAN!!!
				glm::quat rot = glm::quat( this->GetRotationRad( ) - childTransform->GetRotationRad( ) );

				childTransform->SetPosition( this->GetPosition( ) + ( rot * ( childTransform->GetPosition( ) - this->GetPosition( ) ) ) );

				childTransform->Rotate( rotate );
			};
		};
	};

	///-----------------------------------------------------

	void Transform::ScaleChildren( GLfloat scale ) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren( );
		for ( std::shared_ptr<Entity> child : children ) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>( );
			if ( childTransform != nullptr ) {
				childTransform->Scale( scale );
			};
		};
	};

	void Transform::ScaleChildren( glm::vec3 scale ) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren( );
		for ( std::shared_ptr<Entity> child : children ) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>( );
			if ( childTransform != nullptr ) {
				childTransform->Scale( scale );
			};
		};
	};
};