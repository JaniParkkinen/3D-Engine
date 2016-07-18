#include <Core/Components/Texture.hpp>

namespace Engine {

	Texture::Texture( const char* source, size_t flag ) : Component( flag ) {
		std::shared_ptr<Engine::Resource> tex = ResourceManager::GetInstance( )->LoadResource( source );

		// Create one OpenGL texture
		glGenTextures( 1, &texid );

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture( GL_TEXTURE_2D, texid );

		// Give the image to OpenGL
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex->getImageData( ).size.x, tex->getImageData( ).size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tex->getImageData( ).imageData[0] );

		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	}

	void Texture::Init( ) { }

	void Texture::Cleanup( ) { }

	void Texture::Bind( ) {
		if ( ( _type & TEXTURE ) == TEXTURE ) {
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, texid );
		}
		else if ( ( _type & NORMAL_MAP ) == NORMAL_MAP ) {
			glActiveTexture( GL_TEXTURE1 );
			glBindTexture( GL_TEXTURE_2D, texid );
		}
	}

	void Texture::Unbind( ) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
