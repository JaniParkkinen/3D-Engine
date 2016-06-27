#include <Core/Components/LightSource.hpp>

namespace Engine {
	LightSource::LightSource( glm::vec4 color, float intensity )
	: _color(color), _intensity(intensity), Component(LIGHTSOURCE) {

	}

	LightSource::~LightSource( ) {

	}

	void LightSource::Init( ) {

	}

	void LightSource::Cleanup( ) {

	}

	void LightSource::Bind( GLuint shaderID ) {
		GLint LightPosition		= glGetUniformLocation( shaderID, "LightPosition" );
		GLint LightColor		= glGetUniformLocation( shaderID, "LightColor" );
		GLint LightIntensity	= glGetUniformLocation( shaderID, "LightIntensity" );

		if ( LightPosition != -1 ) {
			glUniform3fv( LightPosition, 1, glm::value_ptr( _owner->GetComponent<Transform>( TRANSFORM )->GetPosition( ) ) );
		}
		if ( LightColor != -1 ) {
			glUniform4fv( LightColor, 1, glm::value_ptr( _color ) );
		}
		if ( LightIntensity != -1 ) {
			glUniform1f( LightIntensity, _intensity );
		}
	}
}