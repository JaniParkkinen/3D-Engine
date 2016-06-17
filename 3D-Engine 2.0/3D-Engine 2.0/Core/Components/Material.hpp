#ifndef Engine_Material_hpp
#define Engine_Material_hpp

#include <vector>

#include <GLM/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Material : public Component {
	public:
		Material( std::vector<tinyobj::material_t> materials) : _materials(materials) { };
		virtual ~Material( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		std::vector<tinyobj::material_t> getMaterials() { return _materials; }

	private:
		std::vector<tinyobj::material_t> _materials;
	};
};
#endif
