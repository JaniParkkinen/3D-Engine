#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <vector>

#include <GLM/glm.hpp>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#endif
#include <Core/Time.hpp>
#include <Core/Buffer.hpp>

#include <Core/Managers/EntityManager.hpp>

#include <Core/Resource.h>

//#include <Core/Components/Mesh.h>

namespace Engine {

	class Render : public Component {
	public:
		Render(std::vector<tinyobj::shape_t> shapes) : _shapes(shapes), _indices(0), Component(RENDERABLE) { };
		virtual ~Render() { };

		virtual void bind(Buffer& vertexBuffer, Buffer& indexBuffer, GLuint shaderID);

		virtual void unbind();

		size_t GetIndices() { return _indices; }


		virtual void Init() override;
		virtual void Cleanup() override;

		std::vector<tinyobj::shape_t> getShapes() { return _shapes; };
		std::vector<glm::vec3> getVertexData();
		//std::vector<Engine::Mesh> getAnimShape() { return _animShapes; };

		void ScaleTexture(float scale);
		void ScaleTexture(glm::vec2 scale);
		void ScaleTexture(float x, float y);
		
	private:
		std::vector<tinyobj::shape_t> _shapes;
		//std::vector<Engine::Mesh> _animShapes;
		std::vector<glm::vec3> _tangents;
		std::vector<glm::vec3> _bitangents;

		size_t _indices;
		//Mesh* Mesh;
		
		unsigned index;
	};
}
#endif
