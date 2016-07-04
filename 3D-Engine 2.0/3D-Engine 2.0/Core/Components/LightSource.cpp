#include <Core/Components/LightSource.hpp>
#include <cstdio>

namespace Engine {
	DirectionalLight::DirectionalLight( glm::vec3 direction, glm::vec3 color, size_t id, float ambientIntensity, float diffuseIntensity, size_t flag )
		: _direction( direction ), _id( id ), BaseLight( color, ambientIntensity, diffuseIntensity, flag ) {

	}

	DirectionalLight::~DirectionalLight( ) {

	}

	void DirectionalLight::Bind( GLuint shaderID ) {
		GLint position;

		char name[ 128 ];
		memset( name, 0, sizeof( name ) );
		snprintf( name, sizeof( name ), "gDirectionalLights[%d].Base.Color", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _color ) );
		}

		snprintf( name, sizeof( name ), "gDirectionalLights[%d].Base.AmbientIntensity", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _ambientIntensity );
		}

		snprintf( name, sizeof( name ), "gDirectionalLights[%d].Base.DiffuseIntensity", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _diffuseIntensity );
		}

		snprintf( name, sizeof( name ), "gDirectionalLights[%d].Direction", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _direction ) );
		}
	}

	PointLight::PointLight( Attenuation attenuation, size_t id, glm::vec3 color, float ambientIntensity, float diffuseIntensity, size_t flag )
		: _attenuation( attenuation ), _id( id ), BaseLight( color, ambientIntensity, diffuseIntensity, flag ) {

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

	SpotLight::SpotLight( glm::vec3 direction, float cutoff, size_t id, glm::vec3 atten, glm::vec3 color, float ambientIntensity, float diffuseIntensity, size_t flag )
		: _direction( direction ), _cutoff( cutoff ), _id( id ), PointLight( atten, id, color, ambientIntensity, diffuseIntensity, flag ) {

	}

	void SpotLight::Bind( GLuint shaderID ) {
		GLint position;

		char name[ 128 ];
		memset( name, 0, sizeof( name ) );
		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Base.Color", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _color ) );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Base.AmbientIntensity", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _ambientIntensity );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Base.DiffuseIntensity", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _diffuseIntensity );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Position", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _owner->GetComponent<Transform>( TRANSFORM )->GetPosition( ) ) );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Atten.Constant", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _attenuation.Constant );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Atten.Linear", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _attenuation.Linear );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Base.Atten.Exp", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _attenuation.Exp );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Direction", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform3fv( position, 1, glm::value_ptr( _direction ) );
		}

		snprintf( name, sizeof( name ), "gSpotLights[%d].Cutoff", _id );

		position = glGetUniformLocation( shaderID, name );

		if ( position != -1 ) {
			glUniform1f( position, _cutoff );
		}
	}
}
