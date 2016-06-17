#include <Core/Components/Renderable.hpp>

namespace Engine {

	void Render::bind( Buffer& vertexBuffer, Buffer& indexBuffer, GLuint shaderID ) {

		std::vector<GLfloat> vertexVector;
		std::vector<GLfloat> uvVector;
		std::vector<GLfloat> normalVector;
		std::vector<size_t> indiceVector;

		for ( int i = 0; i < _shapes.size( ); i++ ) {
			for ( size_t ind : _shapes[ i ].mesh.indices ) { ind += vertexVector.size( ); }
			vertexVector.insert( vertexVector.end( ), _shapes[ i ].mesh.positions.begin( ), _shapes[ i ].mesh.positions.end( ) );
			uvVector.insert( uvVector.end( ), _shapes[ i ].mesh.texcoords.begin( ), _shapes[ i ].mesh.texcoords.end( ) );
			normalVector.insert( normalVector.end( ), _shapes[ i ].mesh.normals.begin( ), _shapes[ i ].mesh.normals.end( ) );
			indiceVector.insert( indiceVector.end( ), _shapes[ i ].mesh.indices.begin( ), _shapes[ i ].mesh.indices.end( ) );
		}

		_vertices	= vertexVector.size( );
		_uvs		= uvVector.size( );
		_normals	= normalVector.size( );
		_indices	= indiceVector.size( );

		vertexVector.insert( vertexVector.end( ), uvVector.begin( ), uvVector.end( ) );
		vertexVector.insert( vertexVector.end( ), normalVector.begin( ), normalVector.end( ) );

		vertexBuffer.BindBufferData( vertexVector.size( ), vertexVector.data( ) );
		indexBuffer.BindBufferData( indiceVector.size( ), indiceVector.data( ) );

		GLint PositionLocation		= glGetAttribLocation( shaderID, "in_Position" );
		GLint TexCoordinateLocation	= glGetAttribLocation( shaderID, "in_TexCoord" );
		GLint NormalLocation		= glGetAttribLocation( shaderID, "in_Normal" );

		if ( PositionLocation != -1 ) {
			glEnableVertexAttribArray( PositionLocation );
			glVertexAttribPointer( PositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), ( void* )( 0 * sizeof( GLfloat ) ) );
		}; //if (PositionLocation != -1)

		if ( TexCoordinateLocation != -1 ) {
			glEnableVertexAttribArray( TexCoordinateLocation );
			glVertexAttribPointer( TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), ( void* )( _vertices * sizeof( GLfloat ) ) );
		}; //if (TexCoordinateLocation != -1)

		if ( NormalLocation != -1 ) {
			glEnableVertexAttribArray( NormalLocation );
			glVertexAttribPointer( NormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), ( void* )( (_vertices + _uvs) * sizeof( GLfloat ) ) );
		}; //if (NormalLocation != -1)
	}

	void Render::unbind( ) { }

	void Render::Init( ) { }

	void Render::Cleanup( ) { }
};