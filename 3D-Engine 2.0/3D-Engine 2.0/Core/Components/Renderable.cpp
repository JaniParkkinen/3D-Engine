#include <Core/Components/Renderable.hpp>

namespace Engine {

	void Render::bind( Buffer& vertexBuffer, Buffer& indexBuffer, GLuint shaderID ) {

		std::vector<GLfloat> vertexVector;
		std::vector<GLfloat> uvVector;
		std::vector<GLfloat> normalVector;
		std::vector<size_t> indiceVector;

		for ( size_t i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t ind : _shapes[ i ].mesh.indices ) { ind += vertexVector.size( ); }
			vertexVector.insert( vertexVector.end( ), _shapes[ i ].mesh.positions.begin( ), _shapes[ i ].mesh.positions.end( ) );
			uvVector.insert( uvVector.end( ), _shapes[ i ].mesh.texcoords.begin( ), _shapes[ i ].mesh.texcoords.end( ) );
			normalVector.insert( normalVector.end( ), _shapes[ i ].mesh.normals.begin( ), _shapes[ i ].mesh.normals.end( ) );
			indiceVector.insert( indiceVector.end( ), _shapes[ i ].mesh.indices.begin( ), _shapes[ i ].mesh.indices.end( ) );
		}

		size_t vertices		= vertexVector.size( );
		size_t uvs			= uvVector.size( );
		size_t normals		= normalVector.size( );
		_indices			= indiceVector.size( );		

		size_t tangents		= _tangents.size();
		size_t bitangents	= _bitangents.size();

		vertexVector.insert( vertexVector.end( ), uvVector.begin( ), uvVector.end( ) );
		vertexVector.insert( vertexVector.end( ), normalVector.begin( ), normalVector.end( ) );

		for (size_t i = 0; i < _tangents.size(); i++) {
			vertexVector.push_back(_tangents[i].x);
			vertexVector.push_back(_tangents[i].y);
			vertexVector.push_back(_tangents[i].z);
		} for (size_t i = 0; i < _bitangents.size(); i++) {
			vertexVector.push_back(_bitangents[i].x);
			vertexVector.push_back(_bitangents[i].y);
			vertexVector.push_back(_bitangents[i].z);
		}

		vertexBuffer.BindBufferData( vertexVector.size( ), vertexVector.data( ) );
		indexBuffer.BindBufferData( indiceVector.size( ), indiceVector.data( ) );

		GLint PositionLocation		= glGetAttribLocation( shaderID, "in_Position" );
		GLint TexCoordinateLocation	= glGetAttribLocation( shaderID, "in_TexCoord" );
		GLint NormalLocation		= glGetAttribLocation( shaderID, "in_Normal" );
		GLint TangentLocation		= glGetAttribLocation( shaderID, "in_Tangent" );
		GLint BitangentLocation		= glGetAttribLocation( shaderID, "in_Bitangent" );

		if ( PositionLocation != -1 ) {
			glEnableVertexAttribArray( PositionLocation );
			glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, ( void* )( 0 * sizeof( GLfloat ) ) );
		} //if (PositionLocation != -1)


		if ( TexCoordinateLocation != -1 ) {
			glEnableVertexAttribArray( TexCoordinateLocation );
			glVertexAttribPointer( TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, ( void* )( vertices * sizeof( GLfloat ) ) );
		} //if (TexCoordinateLocation != -1)

		if ( NormalLocation != -1 ) {
			glEnableVertexAttribArray( NormalLocation );
			glVertexAttribPointer( NormalLocation, 3, GL_FLOAT, GL_FALSE, 0, ( void* )( ( vertices + uvs ) * sizeof( GLfloat ) ) );
		} //if (NormalLocation != -1)
		if ( TangentLocation != -1) {
			glEnableVertexAttribArray( TangentLocation );
			glVertexAttribPointer( TangentLocation, 3, GL_FLOAT, GL_FALSE, 0, (void* )( (vertices + uvs + normals ) * sizeof(GLfloat ) ) );
		} //if (TangentLocation != -1)
		if ( BitangentLocation != -1) {
			glEnableVertexAttribArray(BitangentLocation);
			glVertexAttribPointer(BitangentLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)((vertices + uvs + normals + tangents) * sizeof(GLfloat)));
		} //if (BitangentLocation != -1)
	}

	void Render::unbind( ) { }

	void Render::Init( ) { 
		std::vector<glm::vec3> vertexVector;
		std::vector<glm::vec2> uvVector;
		std::vector<glm::vec3> tangents;
		std::vector<glm::vec3> bitangents;

		glm::vec2 deltaUV1;
		glm::vec2 deltaUV2;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		glm::vec3 deltaPos1;
		glm::vec3 deltaPos2;

		for (size_t i = 0; i < _shapes.size(); i++) {
			vertexVector.insert(vertexVector.end(), _shapes[i].mesh.positions.begin(), _shapes[i].mesh.positions.end());
			uvVector.insert(uvVector.end(), _shapes[i].mesh.texcoords.begin(), _shapes[i].mesh.texcoords.end());
		}

		///*glm::mat3x3*/ invTBN = glm::inverse(TBN);

		for (size_t i = 0; i < _shapes.size(); i++) {
			for (size_t ind : _shapes[i].mesh.indices) { ind += vertexVector.size(); }
			deltaPos1 = (vertexVector[i + 1]) - vertexVector[i];
			deltaPos2 = (vertexVector[i + 2]) - vertexVector[i];

			deltaUV1 = uvVector[i + 1] - uvVector[i];
			deltaUV2 = uvVector[i + 2] - uvVector[i];
		}
	
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		deltaPos1 = deltaUV1.x * tangent + deltaUV1.y * bitangent;
		deltaPos2 = deltaUV2.x * tangent + deltaUV2.y * bitangent;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

	void Render::Cleanup( ) { }

	std::vector<glm::vec3> Render::getVertexData( ) {
		std::vector<glm::vec3> vertices;
		for ( size_t i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t k = 0; k < ( _shapes[ i ].mesh.positions.size( ) / 3 ); k++ ) {
				vertices.push_back( glm::vec3( _shapes[ i ].mesh.positions[ 3 * k + 0 ], _shapes[ i ].mesh.positions[ 3 * k + 1 ], _shapes[ i ].mesh.positions[ 3 * k + 2 ] ) );
			}
		}
		return vertices;
	}

	void Render::ScaleTexture( float scale ) {
		scale = 1.0f / scale;
		for ( size_t i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t k = 0; k < _shapes[ i ].mesh.texcoords.size( ); k++ ) {
				_shapes[ i ].mesh.texcoords[ k ] *= scale;
			}
		}
	}

	void Render::ScaleTexture( glm::vec2 scale ) {
		scale = 1.0f / scale;
		for ( size_t i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t k = 0; k < _shapes[ i ].mesh.texcoords.size( ); k++ ) {
				if ( k % 2 == 0 ) {
					_shapes[ i ].mesh.texcoords[ k ] *= scale.x;
				} else {
					_shapes[ i ].mesh.texcoords[ k ] *= scale.y;
				}
			}
		}
	}

	void Render::ScaleTexture( float x, float y ) {
		x = 1.0f / x;
		y = 1.0f / y;
		for ( size_t i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t k = 0; k < _shapes[ i ].mesh.texcoords.size( ); k++ ) {
				if ( k % 2 == 0 ) {
					_shapes[ i ].mesh.texcoords[ k ] *= x;
				} else {
					_shapes[ i ].mesh.texcoords[ k ] *= y;
				}
			}
		}
	}
}
