#include <Core/Systems/PhysicsSystem.hpp>

namespace Engine {
	void PhysicsSystem::Init( ) {
		_entityManager = EntityManager::GetInstance( );
	};

	void PhysicsSystem::Cleanup( ) {

	};

	void PhysicsSystem::Pause( ) {

	};

	void PhysicsSystem::Resume( ) {

	};

	void PhysicsSystem::Update( DeltaTime deltaTime ) {
		std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities( );
		for ( std::shared_ptr<Entity> entity : entities ) {

			if ( (entity->GetKey() & PHYSICS) == PHYSICS ) {
				std::shared_ptr<Transform> transform = entity->GetComponent<Transform>( TRANSFORM );
				std::shared_ptr<Render> renderable = entity->GetComponent<Render>( RENDERABLE );
				std::shared_ptr<AxisAlignedBoundingBox> aabb = entity->GetComponent<AxisAlignedBoundingBox>( AABB );

				glm::mat4 scale = glm::mat4( 1 );
				glm::mat4 rotation = glm::mat4( 1 );
				glm::mat4 position = glm::mat4( 1 );

				std::vector<glm::vec3> vertexData = renderable->getVertexData( );
				std::vector<glm::vec4> transVertDat;

				scale = glm::scale( scale, transform->GetScale( ) );

				rotation = glm::rotate( rotation, transform->GetRotationRad( ).x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
				rotation = glm::rotate( rotation, transform->GetRotationRad( ).y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
				rotation = glm::rotate( rotation, transform->GetRotationRad( ).z, glm::vec3( 0.0f, 0.0f, 1.0f ) );

				glm::mat4 trans;

				trans = rotation * scale;

				for ( size_t i = 0; i < vertexData.size( ); i++ ) {
					if ( i % 3 == 0 ) {
						transVertDat.push_back( trans * glm::vec4( vertexData[ i ], 1 ) );
					};
				};

				glm::vec3 min = glm::vec3( transVertDat[ 0 ].x, transVertDat[ 0 ].y, transVertDat[ 0 ].z );
				glm::vec3 max = glm::vec3( transVertDat[ 0 ].x, transVertDat[ 0 ].y, transVertDat[ 0 ].z );

				for ( size_t i = 0; i < transVertDat.size( ); i++ ) {
					if ( transVertDat[ i ].x < min.x ) { min.x = transVertDat[ i ].x; }
					if ( transVertDat[ i ].y < min.y ) { min.y = transVertDat[ i ].y; }
					if ( transVertDat[ i ].z < min.z ) { min.z = transVertDat[ i ].z; }
					if ( transVertDat[ i ].x > max.x ) { max.x = transVertDat[ i ].x; }
					if ( transVertDat[ i ].y > max.y ) { max.y = transVertDat[ i ].y; }
					if ( transVertDat[ i ].z > max.z ) { max.z = transVertDat[ i ].z; }
				}; //for (size_t i = 0; i < transVertDat.size(); i++)

				aabb->UpdateAABB( min, max );
			}; //if (transformable != nullptr && renderable != nullptr)
		}; //for (auto it = entities.begin(); it != entities.end(); it++)
	};

	bool PhysicsSystem::CheckAABBCollision( std::shared_ptr<Entity> lhsEntity, std::shared_ptr<Entity> rhsEntity ) {
		if ( ((lhsEntity->GetKey() & AABB) == AABB) && ((rhsEntity->GetKey() & AABB) == AABB) ) {
			std::shared_ptr<AxisAlignedBoundingBox> lhsAABB = lhsEntity->GetComponent<AxisAlignedBoundingBox>( AABB );
			std::shared_ptr<AxisAlignedBoundingBox> rhsAABB = rhsEntity->GetComponent<AxisAlignedBoundingBox>( AABB );

			std::shared_ptr<Transform> lhsTransform = lhsEntity->GetComponent<Transform>( TRANSFORM );
			std::shared_ptr<Transform> rhsTransform = rhsEntity->GetComponent<Transform>( TRANSFORM );

			glm::mat4 lhsModel = glm::translate( glm::mat4( 1 ), lhsTransform->GetPosition( ) );
			glm::mat4 rhsModel = glm::translate( glm::mat4( 1 ), rhsTransform->GetPosition( ) );

			glm::vec4 lhsTransMin = lhsModel * glm::vec4( lhsAABB->_min, 1.0f );
			glm::vec4 lhsTransMax = lhsModel * glm::vec4( lhsAABB->_max, 1.0f );
			glm::vec4 rhsTransMin = rhsModel * glm::vec4( rhsAABB->_min, 1.0f );
			glm::vec4 rhsTransMax = rhsModel * glm::vec4( rhsAABB->_max, 1.0f );

			if ( lhsTransMin.x > rhsTransMax.x ) return false;
			if ( lhsTransMax.x < rhsTransMin.x ) return false;
			if ( lhsTransMin.y > rhsTransMax.y ) return false;
			if ( lhsTransMax.y < rhsTransMin.y ) return false;
			if ( lhsTransMin.z > rhsTransMax.z ) return false;
			if ( lhsTransMax.z < rhsTransMin.z ) return false;

			return true;
		};
		return false;
	};
};
