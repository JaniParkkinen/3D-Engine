#include <Core/Systems/RenderingSystem.hpp>

namespace Engine {
	void RenderingSystem::Init( ) {
		_entityManager = EntityManager::GetInstance( );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_LIGHTING );

		glUseProgram( 0 );

		_vertexBuffer.CreateBuffer( GL_ARRAY_BUFFER );
		_indiceBuffer.CreateBuffer( GL_ELEMENT_ARRAY_BUFFER );

		glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
	};

	void RenderingSystem::Cleanup( ) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		SwapBuffers( _window->GetHDC( ) );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	};

	void RenderingSystem::Pause( ) {
		if ( !_paused ) {
			_paused = true;
		}
	};

	void RenderingSystem::Resume( ) {
		if ( _paused ) {
			_paused = false;
		}
	};

	void RenderingSystem::Update( DeltaTime deltaTime ) {
		if ( !_paused ) {
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities( );
			for ( std::shared_ptr<Entity> entity : entities ) {

				//Get components needded for rendering
				std::shared_ptr<Transform>	transform = entity->GetComponent<Transform>( );
				std::shared_ptr<Render>		render = entity->GetComponent<Render>( );
				std::shared_ptr<AxisAlignedBoundingBox>		aabb = entity->GetComponent<AxisAlignedBoundingBox>( );
				std::shared_ptr<Texture>	texture = entity->GetComponent<Texture>( );
				std::shared_ptr<Shader>		shader = entity->GetComponent<Shader>( );

				//Check for the bare minimum components needed for rendering
				if ( transform != nullptr && render != nullptr ) {

					//If entity has shader component use it. Otherwise use default shader
					GLuint shaderID;
					if ( shader != nullptr ) { shaderID = shader->GetProgramID( ); };
					glUseProgram( shaderID );

					//Get Data
					glm::mat4 Model = glm::translate( glm::mat4( 1 ), transform->GetPosition( ) );

					glm::mat4 Scale = glm::scale( glm::mat4( 1 ), transform->GetScale( ) );

					glm::mat4 Rotate = glm::toMat4( transform->GetRotationQuat( ) );

					Model = Model * Rotate * Scale;

					glm::mat4 View = _cam->GetViewMatrix( );

					glm::mat4 Projection = glm::perspective( glm::radians( 60.0f ), _window->GetSize( ).x / _window->GetSize( ).y, 0.01f, 400.0f );

					glm::vec3 ViewPosition = _cam->GetPosition( );

					glm::vec3 LightPosition = glm::vec3( 150.0f, 150.0f, 0.0f );

					//Bind Data
					if ( texture != nullptr ) {
						texture->BindTexture( shaderID );
					};

					_vertexBuffer.BindBufferData( render->GetVertexData( ).size( ), &render->GetVertexData( )[ 0 ].x );
					_indiceBuffer.BindBufferData( render->GetIndiceData( ).size( ), &render->GetIndiceData( )[ 0 ].x );

					GLint ModelLocation = glGetUniformLocation( shaderID, "Model" );
					GLint ViewLocation = glGetUniformLocation( shaderID, "View" );
					GLint ProjectionLocation = glGetUniformLocation( shaderID, "Projection" );
					GLint ViewPositionLocation = glGetUniformLocation( shaderID, "ViewPosition" );
					GLint LightPositionLocation = glGetUniformLocation( shaderID, "LightPosition" );

					GLint PositionLocation = glGetAttribLocation( shaderID, "in_Position" );
					GLint TexCoordinateLocation = glGetAttribLocation( shaderID, "in_TexCoord" );
					GLint NormalLocation = glGetAttribLocation( shaderID, "in_Normal" );

					glUniformMatrix4fv( ModelLocation, 1, GL_FALSE, glm::value_ptr( Model ) );
					glUniformMatrix4fv( ViewLocation, 1, GL_FALSE, glm::value_ptr( View ) );
					glUniformMatrix4fv( ProjectionLocation, 1, GL_FALSE, glm::value_ptr( Projection ) );
					glUniform3fv( ViewPositionLocation, 1, glm::value_ptr( ViewPosition ) );
					glUniform3fv( LightPositionLocation, 1, glm::value_ptr( LightPosition ) );

					if ( shader != nullptr ) { shader->BindShader( ); };

					if ( PositionLocation != -1 ) {
						glEnableVertexAttribArray( PositionLocation );
						glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 0 * sizeof( GLfloat ) ) );
					}; //if (PositionLocation != -1)

					if ( TexCoordinateLocation != -1 ) {
						glEnableVertexAttribArray( TexCoordinateLocation );
						glVertexAttribPointer( TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 3 * sizeof( GLfloat ) ) );
					}; //if (TexCoordinateLocation != -1)

					if ( NormalLocation != -1 ) {
						glEnableVertexAttribArray( NormalLocation );
						glVertexAttribPointer( NormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( glm::vec3 ), ( void* )( 6 * sizeof( GLfloat ) ) );
					}; //if (NormalLocation != -1)

					  //Draw object
					glDrawElements( GL_TRIANGLES, render->GetIndiceData( ).size( ) * 3, GL_UNSIGNED_INT, ( void* )0 );
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
						}; //if (PositionLocation != -1)

						glDrawElements( GL_LINE_STRIP, aabb->GetIndiceData( ).size( ) * 3, GL_UNSIGNED_INT, ( void* )0 );
					}; //if (aabb != nullptr)
					#endif // DRAW_AABB

				}; //if (transform != nullptr && render != nullptr)
			}; //for (std::shared_ptr<Entity> entity : entities)

			SwapBuffers( _window->GetHDC( ) );
			glUseProgram( 0 );

		} //if (!_paused)
	};
};
