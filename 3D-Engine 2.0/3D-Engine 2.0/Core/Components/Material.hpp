#ifndef Engine_Material_hpp
#define Engine_Material_hpp

#include <vector>

#include <GL/glew.h>

#include <GLM/glm.hpp>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>
#endif

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Material : public Component {
	public:
		Material(std::vector<tinyobj::material_t> materials);
		virtual ~Material( );

		virtual void bind(GLuint shaderID);

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		std::vector<tinyobj::material_t> getMaterials() { return _materials; }

	private:
		std::vector<tinyobj::material_t> _materials;
	};
};
#endif
