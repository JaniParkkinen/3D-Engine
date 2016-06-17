#ifndef Engine_Material_hpp
#define Engine_Material_hpp

#include <glm/glm.hpp>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Material : public Component {
	public:
		Material( glm::vec3 emission, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 transmittance, float ior, float shininess, float dissolve, float illum, float dummy )
			:_emission( emission ), _ambient( ambient ), _diffuse( diffuse ), _specular( specular ), _transmittance( transmittance ), _ior( ior ), _shininess( shininess ), _dissolve( dissolve ), _illum( illum ), _dummy( dummy ) { };
		virtual ~Material( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		void SetEmission( glm::vec3 emission ) { _emission = emission; };
		void SetAmbient( glm::vec3 ambient ) { _ambient = ambient; };
		void SetDiffuse( glm::vec3 diffuse ) { _diffuse = diffuse; };
		void SetSpecular( glm::vec3 specular ) { _specular = specular; };
		void SetTransmittance( glm::vec3 transmittance ) { _transmittance = transmittance; };

		void SetIor( float ior ) { _ior = ior; };
		void SetShininess( float shininess ) { _shininess = shininess; };
		void SetDissolve( float dissolve ) { _dissolve = dissolve; };
		void SetIllum( float illum ) { _illum = illum; };
		void SetDummy( float dummy ) { _dummy = dummy; };

		glm::vec3 GetEmission( ) { return _emission; };
		glm::vec3 GetAmbient( ) { return _ambient; };
		glm::vec3 GetDiffuse( ) { return _diffuse; };
		glm::vec3 GetSpecular( ) { return _specular; };
		glm::vec3 GetTransmittance( ) { return _transmittance; };

		float GetIor( ) { return _ior; };
		float GetShininess( ) { return _shininess; };
		float GetDissolve( ) { return _dissolve; };
		float GetIllum( ) { return _illum; };
		float GetDummy( ) { return _dummy; };

		glm::vec3 const & GetEmissionRef( ) { return _emission; };
		glm::vec3 const & GetAmbientRef( ) { return _ambient; };
		glm::vec3 const & GetDiffuseRef( ) { return _diffuse; };
		glm::vec3 const & GetSpecularRef( ) { return _specular; };
		glm::vec3 const & GetTransmittanceRef( ) { return _transmittance; };

		float const & GetIorRef( ) { return _ior; };
		float const & GetShininessRef( ) { return _shininess; };
		float const & GetDissolveRef( ) { return _dissolve; };
		float const & GetIllumRef( ) { return _illum; };
		float const & GetDummyRef( ) { return _dummy; };

	private:
		glm::vec3 _emission;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		glm::vec3 _transmittance;

		float _ior;
		float _shininess;
		float _dissolve;
		float _illum;
		float _dummy;
	};
};
#endif
