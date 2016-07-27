#include <Core/Systems/RenderingSystem.hpp>

namespace Engine {
	void RenderingSystem::Init( ) {
		_entityManager = EntityManager::GetInstance( );

		glEnable( GL_DEPTH_TEST );
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		glEnable( GL_CULL_FACE );
		//glEnable( GL_NORMALIZE );

		glUseProgram( 0 );

		_vertexBuffer.CreateBuffer( GL_ARRAY_BUFFER );
		_indexBuffer.CreateBuffer( GL_ELEMENT_ARRAY_BUFFER );

		glClearColor( 0.10f, 0.10f, 0.10f, 1.0f );
	} // Init

	void RenderingSystem::Cleanup( ) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		SwapBuffers( _window->GetHDC( ) );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	} // Cleanup

	void RenderingSystem::Pause( ) {
		_paused = true;
	} // Pause

	void RenderingSystem::Resume( ) {
		_paused = false;
	} // Resume

	void RenderingSystem::Update( DeltaTime deltaTime ) {
		if ( !_paused ) {
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			std::vector<std::shared_ptr<Entity>> dirLights = _entityManager->GetEntities( DIRECTIONAL_LIGHT );
			std::vector<std::shared_ptr<Entity>> pointLights = _entityManager->GetEntities( POINT_LIGHT );
			std::vector<std::shared_ptr<Entity>> spotLights = _entityManager->GetEntities( SPOT_LIGHT );

			std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities( );

			for ( std::shared_ptr<Entity> entity : entities ) {
				//Check if entity has rendering flags
				if ( ( entity->GetKey( ) & RENDER ) == RENDER ) {

					GLAssert( );

					// Get components needed for rendering
					std::shared_ptr<AxisAlignedBoundingBox>		aabb = entity->GetComponent<AxisAlignedBoundingBox>( AABB );
					std::shared_ptr<Material>					material = entity->GetComponent<Material>( MATERIAL );
					std::shared_ptr<Render>						render = entity->GetComponent<Render>( RENDERABLE );
					std::shared_ptr<Shader>						shader = entity->GetComponent<Shader>( SHADER );
					std::shared_ptr<Texture>					texture = entity->GetComponent<Texture>( TEXTURE );
					std::shared_ptr<Texture>					normal = entity->GetComponent<Texture>( NORMAL_MAP );
					std::shared_ptr<Transform>					transform = entity->GetComponent<Transform>( TRANSFORM );

					GLAssert( );

					GLuint shaderID = shader->GetProgramID( );
					glUseProgram( shaderID );

					GLAssert( );

					// Get Data
					glm::mat4 translate = glm::translate( glm::mat4( 1.0f ), transform->GetPosition( ) );

					glm::mat4 Scale = glm::scale( glm::mat4( 1.0f ), transform->GetScale( ) );

					glm::mat4 Rotate = glm::toMat4( transform->GetRotationQuat( ) );

					glm::mat4 Model = translate * Rotate * Scale;

					//glm::mat4 View = glm::lookAt( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

					glm::mat4 View = _cam->GetViewMatrix( );

					glm::mat4 Projection = glm::perspective( glm::radians( 60.0f ), _window->GetSize( ).x / _window->GetSize( ).y, 0.01f, 400.0f );

					//glm::vec3 ViewPosition = glm::vec3( 0.0f, 0.0f, 0.0f );

					glm::vec3 ViewPosition = _cam->GetPosition( );

					GLAssert( ); 
					// Bind Data
					glUniform1i( glGetUniformLocation( shaderID, "gNumDirectionalLight" ), dirLights.size( ) );
					for ( std::shared_ptr<Entity> light : dirLights ) {
						light->GetComponent<DirectionalLight>( DIRECTIONAL_LIGHT )->Bind( shaderID );

					}

					glUniform1i( glGetUniformLocation( shaderID, "gNumPointLights" ), pointLights.size( ) );
					for ( std::shared_ptr<Entity> light : pointLights ) {
						light->GetComponent<PointLight>( POINT_LIGHT )->Bind( shaderID );
					}

					glUniform1i( glGetUniformLocation( shaderID, "gNumSpotLights" ), spotLights.size( ) );
					for ( std::shared_ptr<Entity> light : spotLights ) {
						light->GetComponent<SpotLight>( SPOT_LIGHT )->Bind( shaderID );
					}

					if ( ( entity->GetKey( ) & TEXTURE ) == TEXTURE ) {
						texture->Bind( );
					}

					if ( ( entity->GetKey( ) & NORMAL_MAP ) == NORMAL_MAP ) {
						normal->Bind( );
					}

//					if ((entity->GetKey() & NORMALMAP) == NORMALMAP) {
//						entity->GetComponent<NormalMap>(NORMALMAP)->Bind();
//					}

					if ( ( entity->GetKey( ) & MATERIAL ) == MATERIAL ) {
						material->bind( shaderID );
					}

					GLAssert( );

					GLint ModelLocation = glGetUniformLocation( shaderID, "Model" );
					GLint ViewLocation = glGetUniformLocation( shaderID, "View" );
					GLint ProjectionLocation = glGetUniformLocation( shaderID, "Projection" );
					GLint CameraPosition = glGetUniformLocation( shaderID, "CameraPosition" );

					GLAssert( );

					glUniformMatrix4fv( ModelLocation, 1, GL_FALSE, glm::value_ptr( Model ) );
					glUniformMatrix4fv( ViewLocation, 1, GL_FALSE, glm::value_ptr( View ) );
					glUniformMatrix4fv( ProjectionLocation, 1, GL_FALSE, glm::value_ptr( Projection ) );
					glUniform3fv( CameraPosition, 1, glm::value_ptr( ViewPosition ) );

					shader->BindShader( );

					render->bind( _vertexBuffer, _indexBuffer, shaderID );

					GLAssert( );

					// Draw object
					glDrawElements( GL_TRIANGLES, render->GetIndices( ), GL_UNSIGNED_INT, ( void* )0 );

					if ( (entity->GetKey( ) & TEXTURE) == TEXTURE ) {
						texture->Unbind( );
					}

					if ( ( entity->GetKey( ) & NORMAL_MAP ) == NORMAL_MAP ) {
						normal->Unbind( );
					}
					#define DRAW_AABB
					#ifdef  DRAW_AABB
					if ( ( entity->GetKey( ) & AABB ) == AABB ) {
						_vertexBuffer.BindBufferData( aabb->GetVertexData( ).size( ) * sizeof( glm::vec3 ), &aabb->GetVertexData( )[ 0 ].x );
						_indexBuffer.BindBufferData( aabb->GetIndiceData( ).size( ) * sizeof( glm::uvec3 ), &aabb->GetIndiceData( )[ 0 ].x );

						Model = glm::translate( glm::mat4( 1 ), transform->GetPosition( ) );

						glUniformMatrix4fv( ModelLocation, 1, GL_FALSE, glm::value_ptr( Model ) );
						GLint PositionLocation = glGetAttribLocation( shaderID, "in_Position" );
						if ( PositionLocation != -1 ) {
							glEnableVertexAttribArray( PositionLocation );
							glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, ( void* )( 0 * sizeof( GLfloat ) ) );
						}; // if (PositionLocation != -1)

						glDrawElements( GL_LINE_STRIP, aabb->GetIndiceData( ).size( ) * 3, GL_UNSIGNED_INT, ( void* )0 );
					}; // if (aabb != nullptr)
					#endif // DRAW_AABB

				} // if ( entity->GetKey( ) & RENDER )

			} // for (std::shared_ptr<Entity> entity : entities)

			SwapBuffers( _window->GetHDC( ) );
			glUseProgram( 0 );

		} // if (!_paused)
	} // Update
}
