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

		DirectionalLight( glm::vec3 direction = glm::vec3( 0.0f ), glm::vec3 color = glm::vec3( 1.0f ), float ambientIntensity = 0.5f, float diffuseIntensity = 0.5f );
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

		int _id;

		PointLight( Attenuation attenuation, int id, glm::vec3 color = glm::vec3( 1.0f ), float ambientIntensity = 0.5f, float diffuseIntensity = 0.5f );
		virtual ~PointLight( );

		virtual void Bind( GLuint shaderID ) override;
	};

	//class SpotLight : public BaseLight {
	//public:

	//private:

	//};
};
#endif
