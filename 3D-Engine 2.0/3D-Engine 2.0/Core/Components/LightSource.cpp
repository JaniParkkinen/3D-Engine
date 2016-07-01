#include <Core/Components/LightSource.hpp>
#include <cstdio>

namespace Engine {
	DirectionalLight::DirectionalLight( glm::vec3 direction, glm::vec3 color, float ambientIntensity, float diffuseIntensity )
		: _direction( direction ), BaseLight( color, ambientIntensity, diffuseIntensity, DIRECTIONAL_LIGHT ) {

	}

	DirectionalLight::~DirectionalLight( ) {

	}

	void DirectionalLight::Bind( GLuint shaderID ) {
		GLint position;

		position = glGetUniformLocation( shaderID, "gDirectionalLight.Base.Color" );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _color ) );
		}

		position = glGetUniformLocation( shaderID, "gDirectionalLight.Base.AmbientIntensity" );

		if ( position != -1 ) {
			glUniform1f( position, _ambientIntensity );
		}

		position = glGetUniformLocation( shaderID, "gDirectionalLight.Base.DiffuseIntensity" );

		if ( position != -1 ) {
			glUniform1f( position, _diffuseIntensity );
		}

		position = glGetUniformLocation( shaderID, "gDirectionalLight.Direction" );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _direction ) );
		}
	}

	PointLight::PointLight( Attenuation attenuation, int id, glm::vec3 color, float ambientIntensity, float diffuseIntensity )
		: _attenuation( attenuation ), _id( id ), BaseLight( color, ambientIntensity, diffuseIntensity, POINT_LIGHT ) {

	}

	PointLight::~PointLight( ) {

	}

	void PointLight::Bind( GLuint shaderID ) {
		if ( ( _owner->GetKey( ) & TRANSFORM ) == TRANSFORM ) {
			GLint position;

			char name[ 128 ];
			memset( name, 0, sizeof( name ) );
			snprintf( name, sizeof( name ), "gPointLights[%d].Base.Color", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform3fv( position, 1, glm::value_ptr( _color ) );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Base.AmbientIntensity", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform1f( position, _ambientIntensity );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Base.DiffuseIntensity", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform1f( position, _diffuseIntensity );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Position", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform3fv( position, 1, glm::value_ptr( _owner->GetComponent<Transform>( TRANSFORM )->GetPosition( ) ) );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Atten.Constant", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform1f( position, _attenuation.Constant );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Atten.Linear", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform1f( position, _attenuation.Linear );
			}

			snprintf( name, sizeof( name ), "gPointLights[%d].Atten.Exp", _id );

			position = glGetUniformLocation( shaderID, name );

			if ( position != -1 ) {
				glUniform1f( position, _attenuation.Exp );
			}
		}
	}
}
