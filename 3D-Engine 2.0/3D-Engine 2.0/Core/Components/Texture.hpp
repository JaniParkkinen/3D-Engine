#ifndef Engine_Texture_h
#define Engine_Texture_h

#include <GL/glew.h>

#include <Core/Time.hpp>
#include <Core/Managers/ResourceManager.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	class Texture : public Component {
	public:
		Texture( const char* source );

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		void Bind( );
		void Unbind( );
	private:
		Resource* tex;
		GLuint texid;
	};
};
#endif