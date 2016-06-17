#include <Core/Systems/RenderingSystem.hpp>

namespace Engine {
	void RenderingSystem::Init( ) {
		_entityManager = EntityManager::GetInstance( );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_LIGHTING );

		glUseProgram( 0 );

		_vertexBuffer.CreateBuffer( GL_ARRAY_BUFFER );
		_indiceBuffer.CreateBuffer( GL_ELEMENT_ARRAY_BUFFER );

		glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
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
			//std::vector<LightSource> lightsources = _entityManager->GetComponents<LightSource>( LIGHT );
			std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities( );
			for ( std::shared_ptr<Entity> entity : entities ) {
				//Check if entity has rendering flags
				if ( entity->GetKey( ) & RENDER == RENDER ) {

					// Get components needed for rendering
					std::shared_ptr<AxisAlignedBoundingBox>		aabb = entity->GetComponent<AxisAlignedBoundingBox>( AABB );
					std::shared_ptr<Material>					material = entity->GetComponent<Material>( MATERIAL );
					std::shared_ptr<Render>						render = entity->GetComponent<Render>( RENDERABLE );
					std::shared_ptr<Shader>						shader = entity->GetComponent<Shader>( SHADER );
					std::shared_ptr<Texture>					texture = entity->GetComponent<Texture>( TEXTURE );
					std::shared_ptr<Transform>					transform = entity->GetComponent<Transform>( TRANSFORM );

					glUseProgram( shader->GetProgramID( ) );

					// Get Data
					glm::mat4 translate = glm::translate( glm::mat4( 1.0f ), transform->GetPosition( ) );

					glm::mat4 Scale = glm::scale( glm::mat4( 1.0f ), transform->GetScale( ) );

					glm::mat4 Rotate = glm::toMat4( transform->GetRotationQuat( ) );

					glm::mat4 Model = translate * Rotate * Scale;

					glm::mat4 View = _cam->GetViewMatrix( );

					glm::mat4 Projection = glm::perspective( glm::radians( 60.0f ), _window->GetSize( ).x / _window->GetSize( ).y, 0.01f, 400.0f );

					glm::vec3 ViewPosition = _cam->GetPosition( );


					// Bind Data
					if ( entity->GetKey( ) & TEXTURE == TEXTURE ) {
						texture->BindTexture( shader->GetProgramID( ) );
					};

					//GLint ModelLocation = glGetUniformLocation( shader->GetProgramID( ), "Model" );
					//GLint ViewLocation = glGetUniformLocation( shader->GetProgramID( ), "View" );
					//GLint ProjectionLocation = glGetUniformLocation( shader->GetProgramID( ), "Projection" );
					//GLint ViewPositionLocation = glGetUniformLocation( shader->GetProgramID( ), "ViewPosition" );
					//GLint LightPositionLocation = glGetUniformLocation( shader->GetProgramID( ), "LightPosition" );

					//GLint PositionLocation = glGetAttribLocation( shader->GetProgramID( ), "in_Position" );
					//GLint TexCoordinateLocation = glGetAttribLocation( shader->GetProgramID( ), "in_TexCoord" );
					//GLint NormalLocation = glGetAttribLocation( shader->GetProgramID( ), "in_Normal" );

					//glUniformMatrix4fv( ModelLocation, 1, GL_FALSE, glm::value_ptr( Model ) );
					//glUniformMatrix4fv( ViewLocation, 1, GL_FALSE, glm::value_ptr( View ) );
					//glUniformMatrix4fv( ProjectionLocation, 1, GL_FALSE, glm::value_ptr( Projection ) );
					//glUniform3fv( ViewPositionLocation, 1, glm::value_ptr( ViewPosition ) );
					//glUniform3fv( LightPositionLocation, 1, glm::value_ptr( LightPosition ) );

					shader->BindShader( );

					//if ( PositionLocation != -1 ) {
					//	glEnableVertexAttribArray( PositionLocation );
					//	glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 0 * sizeof( GLfloat ) ) );
					//}; // if (PositionLocation != -1)

					//if ( TexCoordinateLocation != -1 ) {
					//	glEnableVertexAttribArray( TexCoordinateLocation );
					//	glVertexAttribPointer( TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 3 * sizeof( GLfloat ) ) );
					//}; // if (TexCoordinateLocation != -1)

					//if ( NormalLocation != -1 ) {
					//	glEnableVertexAttribArray( NormalLocation );
					//	glVertexAttribPointer( NormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 6 * sizeof( GLfloat ) ) );
					//}; // if (NormalLocation != -1)

					// Draw object
//					glDrawElements( GL_TRIANGLES, render->GetIndiceData( ).size( ) * 3, GL_UNSIGNED_INT, ( void* )0 );
					#ifdef  DRAW_AABB
					if ( aabb != nullptr ) {
						_vertexBuffer.BindBufferData( aabb->GetVertexData( ).size( ), &aabb->GetVertexData( )[ 0 ].x );
						_indiceBuffer.BindBufferData( aabb->GetIndiceData( ).size( ), &aabb->GetIndiceData( )[ 0 ].x );

						Model = glm::translate( glm::mat4( 1 ), transform->GetPosition( ) );

						glUniformMatrix4fv( ModelLocation, 1, GL_FALSE, glm::value_ptr( Model ) );

						if ( PositionLocation != -1 ) {
							glEnableVertexAttribArray( PositionLocation );
							glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof( glm::vec3 ), ( void* )( 0 * sizeof( GLfloat ) ) );
							GLAssert( );
						}; // if (PositionLocation != -1)

						glDrawElements( GL_LINE_STRIP, aabb->GetIndiceData( ).size( ) * 3, GL_UNSIGNED_INT, ( void* )0 );
					}; // if (aabb != nullptr)
					#endif // DRAW_AABB

				}; // for (std::shared_ptr<Entity> entity : entities)

			} // if ( entity->GetKey( ) & RENDER == RENDER )

			SwapBuffers( _window->GetHDC( ) );
			glUseProgram( 0 );

		} // if (!_paused)
	} // Update
}
