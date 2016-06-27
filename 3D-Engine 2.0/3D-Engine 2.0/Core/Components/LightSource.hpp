#ifndef Engine_LightSource_hpp
#define Engine_LightSource_hpp

#include <vector>

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>
#include <Core/Components/Transform.hpp>

namespace Engine {

	class LightSource : public Component {
	public:
		LightSource( glm::vec4 color = glm::vec4( 1.0f ), float intensity = 1.0f );
		virtual ~LightSource( );

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		void Bind( GLuint shaderID );
	private:
		glm::vec4 _color;
		float _intensity;
	};
};
#endif
