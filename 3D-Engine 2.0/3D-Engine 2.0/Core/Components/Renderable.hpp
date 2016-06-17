#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <vector>

#include <GLM/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

#include <Core/Time.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Render : public Component {
	public:
		Render(std::vector<tinyobj::shape_t> shapes) : _shapes(shapes) { };
		virtual ~Render( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		std::vector<tinyobj::shape_t> getShapes( ) { return _shapes; };

	private:
		std::vector<tinyobj::shape_t> _shapes;
	};
};
#endif
