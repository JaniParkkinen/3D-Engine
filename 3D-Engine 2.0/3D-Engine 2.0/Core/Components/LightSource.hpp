#ifndef Engine_LightSource_hpp
#define Engine_LightSource_hpp

#include <vector>

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>
#include <Core/Components/Transform.hpp>

namespace Engine {
	struct BaseLight : public Component {
		glm::vec3 _color;

		float _ambientIntensity;
		float _diffuseIntensity;

		BaseLight( glm::vec3 color, float ambient, float diffuse, size_t flag ) : _color( color ), _ambientIntensity( ambient ), _diffuseIntensity( diffuse ), Component( flag ) { }
		virtual ~BaseLight( ) { }

		virtual void Bind( GLuint shaderID ) = 0;

		virtual void Init( ) override { }
		virtual void Cleanup( ) override { }
	};

	struct DirectionalLight : public BaseLight {
		glm::vec3 _direction;

		size_t _id;

		DirectionalLight( glm::vec3 direction, glm::vec3 color, size_t id, float ambientIntensity, float diffuseIntensity, size_t flag = DIRECTIONAL_LIGHT );
		virtual ~DirectionalLight( );

		virtual void Bind( GLuint shaderID ) override;
	};

	struct PointLight : public BaseLight {
		struct Attenuation {
			float Constant;
			float Linear;
			float Exp;

			Attenuation( glm::vec3 atten ) : Constant( atten.x ), Linear( atten.y ), Exp( atten.z ) { }
		} _attenuation;

		size_t _id;

		PointLight( Attenuation attenuation, size_t id, glm::vec3 color = glm::vec3( 1.0f ), float ambientIntensity = 0.5f, float diffuseIntensity = 0.5f, size_t flag = POINT_LIGHT );
		virtual ~PointLight( );

		virtual void Bind( GLuint shaderID ) override;
	};

	struct SpotLight : public PointLight {
		glm::vec3 _direction;
		float _cutoff;

		size_t _id;

		SpotLight( glm::vec3 direction, float cutoff, size_t id, glm::vec3 atten, glm::vec3 color, float ambientIntensity, float diffuseIntensity, size_t flag = SPOT_LIGHT );

		virtual void Bind( GLuint shaderID ) override;
	};
};
#endif
