#include <Core/Systems/PhysicsSystem.hpp>

namespace Engine {
	void PhysicsSystem::Init( ) {
		_entityManager = EntityManager::GetInstance( );
	}

	void PhysicsSystem::Cleanup( ) {

	}

	void PhysicsSystem::Pause( ) {

	}

	void PhysicsSystem::Resume( ) {

	}

	void PhysicsSystem::Update( DeltaTime deltaTime ) {
		std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities( );
		for ( std::shared_ptr<Entity> entity : entities ) {
			if ( ( entity->GetKey( ) & PHYS ) == PHYS ) {
				if ( entity->GetComponent<Physics>( PHYS )->GetGravity( ) ) {
					entity->GetComponent<Physics>( PHYS )->SetAcceleration( glm::vec3( 0.0f, -100.0f, 0.0f ) );
				} else { entity->GetComponent<Physics>( PHYS )->SetAcceleration( glm::vec3( 0.0f, 0.0f, 0.0f ) ); entity->GetComponent<Physics>( PHYS )->SetVelocity( glm::vec3( entity->GetComponent<Physics>( PHYS )->GetVelocity().x, std::max(0.0f, entity->GetComponent<Physics>( PHYS )->GetVelocity().y), entity->GetComponent<Physics>( PHYS )->GetVelocity().z) ); }
				entity->GetComponent<Physics>( PHYS )->Update( deltaTime );
			}
			if ( ( entity->GetKey( ) & PHYSICS ) == PHYSICS ) {
				std::shared_ptr<Transform> transform = entity->GetComponent<Transform>( TRANSFORM );
				std::shared_ptr<Render> renderable = entity->GetComponent<Render>( RENDERABLE );
				std::shared_ptr<AxisAlignedBoundingBox> aabb = entity->GetComponent<AxisAlignedBoundingBox>( AABB );

				glm::mat4 scale = glm::mat4( 1 );
				glm::mat4 rotation = glm::mat4( 1 );
				glm::mat4 position = glm::mat4( 1 );

				std::vector<glm::vec3> vertexData = renderable->getVertexData( );
				std::vector<glm::vec4> transVertDat;

				scale = glm::scale( scale, transform->GetScale( ) );

				rotation = glm::toMat4( transform->GetRotationQuat( ) );

				glm::mat4 trans;

				trans = rotation * scale;

				for ( size_t i = 0; i < vertexData.size( ); i++ ) {
					transVertDat.push_back( trans * glm::vec4( vertexData[ i ], 1 ) );
				}

				glm::vec3 min = glm::vec3( transVertDat[ 0 ].x, transVertDat[ 0 ].y, transVertDat[ 0 ].z );
				glm::vec3 max = glm::vec3( transVertDat[ 0 ].x, transVertDat[ 0 ].y, transVertDat[ 0 ].z );

				for ( size_t i = 0; i < transVertDat.size( ); i++ ) {
					if ( transVertDat[ i ].x < min.x ) { min.x = transVertDat[ i ].x; }
					if ( transVertDat[ i ].y < min.y ) { min.y = transVertDat[ i ].y; }
					if ( transVertDat[ i ].z < min.z ) { min.z = transVertDat[ i ].z; }
					if ( transVertDat[ i ].x > max.x ) { max.x = transVertDat[ i ].x; }
					if ( transVertDat[ i ].y > max.y ) { max.y = transVertDat[ i ].y; }
					if ( transVertDat[ i ].z > max.z ) { max.z = transVertDat[ i ].z; }
				} //for (size_t i = 0; i < transVertDat.size(); i++)

				aabb->UpdateAABB( min, max );
			} //if (transformable != nullptr && renderable != nullptr)
		} //for (auto it = entities.begin(); it != entities.end(); it++)
	}

	bool PhysicsSystem::CheckAABBCollision( std::shared_ptr<Entity> lhsEntity, std::shared_ptr<Entity> rhsEntity ) {
		if ( ( ( lhsEntity->GetKey( ) & AABB ) == AABB ) && ( ( rhsEntity->GetKey( ) & AABB ) == AABB ) ) {
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
		}
		return false;
	}

	double PhysicsSystem::SquaredDistPointAABB( glm::vec3 & p, std::shared_ptr<Entity> & aabb ) {
		std::shared_ptr<AxisAlignedBoundingBox> rhsAABB = aabb->GetComponent<AxisAlignedBoundingBox>( AABB );

		std::shared_ptr<Transform> rhsTransform = aabb->GetComponent<Transform>( TRANSFORM );

		glm::mat4 rhsModel = glm::translate( glm::mat4( 1 ), rhsTransform->GetPosition( ) );

		glm::vec4 rhsTransMin = rhsModel * glm::vec4( rhsAABB->_min, 1.0f );
		glm::vec4 rhsTransMax = rhsModel * glm::vec4( rhsAABB->_max, 1.0f );

		auto check = [ & ](
			const double pn,
			const double bmin,
			const double bmax ) -> double {
			double out = 0;
			double v = pn;

			if ( v < bmin ) {
				double val = ( bmin - v );
				out += val * val;
			}

			if ( v > bmax ) {
				double val = ( v - bmax );
				out += val * val;
			}

			return out;
		};

		// Squared distance
		double sq = 0.0;

		sq += check( p.x, rhsTransMin.x, rhsTransMax.x );
		sq += check( p.y, rhsTransMin.y, rhsTransMax.y );
		sq += check( p.z, rhsTransMin.z, rhsTransMax.z );

		return sq;
	}

	bool PhysicsSystem::SphereAABBCollision( std::shared_ptr<Entity> sphere, std::shared_ptr<Entity> aabb ) {
		if ( ( ( sphere->GetKey( ) & AABB ) == AABB ) && ( ( aabb->GetKey( ) & AABB ) == AABB ) ) {
			std::shared_ptr<AxisAlignedBoundingBox> lhsAABB = sphere->GetComponent<AxisAlignedBoundingBox>( AABB );
			std::shared_ptr<AxisAlignedBoundingBox> rhsAABB = aabb->GetComponent<AxisAlignedBoundingBox>( AABB );

			std::shared_ptr<Transform> rhsTransform = aabb->GetComponent<Transform>( TRANSFORM );

			glm::mat4 rhsModel = glm::translate( glm::mat4( 1 ), rhsTransform->GetPosition( ) );

			glm::vec4 rhsTransMin = rhsModel * glm::vec4( rhsAABB->_min, 1.0f );
			glm::vec4 rhsTransMax = rhsModel * glm::vec4( rhsAABB->_max, 1.0f );

			float dist_sqrt = lhsAABB->_radius * lhsAABB->_radius;
			glm::vec3 spherePos = sphere->GetComponent<Transform>( TRANSFORM )->GetPosition( );

			double squaredDistance = SquaredDistPointAABB( spherePos, aabb );

			return squaredDistance <= ( lhsAABB->_radius * lhsAABB->_radius );
		}
		return false;
	}

	//bool PhysicsSystem::Gravity(std::shared_ptr<Entity> gravityEntity)
	//{
	//	std::shared_ptr<Transform> gravity = gravityEntity->GetComponent<Transform>(TRANSFORM);
	//	
	//	glm::vec3 gravityModel = Engine::EntityManager::GetInstance()->GetComponent<Engine::Physics>()

	//}
}
