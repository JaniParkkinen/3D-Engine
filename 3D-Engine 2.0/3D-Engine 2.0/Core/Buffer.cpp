#include <Core/Buffer.hpp>
#include <GLM/glm.hpp>

namespace Engine {
	void Buffer::CreateBuffer( GLenum bufferType ) {
		_bufferType = bufferType;

		switch ( _bufferType ) {
			case GL_ARRAY_BUFFER: {
				glGenBuffers( 1, &_bufferID );
				glBindBuffer( _bufferType, _bufferID );
				glBufferData( _bufferType, _bufferSize, NULL, GL_DYNAMIC_DRAW );
				break;
			};
			case GL_ELEMENT_ARRAY_BUFFER: {
				glGenBuffers( 1, &_bufferID );
				glBindBuffer( _bufferType, _bufferID );
				glBufferData( _bufferType, _bufferSize, NULL, GL_DYNAMIC_DRAW );
				break;
			};
			default: {
				std::cout << "Unrecognized buffer type!" << std::endl;
				break;
			};
		};
	};




	void Buffer::BindBufferData( GLuint size, void* data ) {
		switch ( _bufferType ) {
			case GL_ARRAY_BUFFER: {
				if ( size * sizeof( GLfloat ) > _bufferSize ) { Resize( size ); }
				glBufferSubData( _bufferType, 0, sizeof( GLfloat ) * size, data );
				break;
			};
			case GL_ELEMENT_ARRAY_BUFFER: {
				if ( size * sizeof( size_t ) > _bufferSize ) { Resize( size ); }
				glBufferSubData( _bufferType, 0, sizeof( size_t ) * size, data );
				break;
			};
			default: {
				printf_s( "Unrecognized buffer type!\n" );
				break;
			}
		};
	};

	void Buffer::Resize( GLuint size ) {

		switch ( _bufferType ) {
			case GL_ARRAY_BUFFER: {
				while ( _bufferSize < size * sizeof( GLfloat ) ) { _bufferSize *= 2; }
				while ( _bufferSize / 2 > size * sizeof( GLfloat ) ) { _bufferSize /= 2; }
				glBufferData( _bufferType, _bufferSize, 0, GL_DYNAMIC_DRAW );
				break;
			};
			case GL_ELEMENT_ARRAY_BUFFER: {
				while ( _bufferSize < size * sizeof( size_t ) ) { _bufferSize *= 2; }
				while ( _bufferSize / 2 > size * sizeof( size_t ) ) { _bufferSize /= 2; }
				glBufferData( _bufferType, _bufferSize, 0, GL_DYNAMIC_DRAW );
				break;
			};
			default: {
				printf_s( "Undefined buffer type!\n" );
				break;
			};
		};
	};
};