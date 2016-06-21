#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <vector>

#include <GLM/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

#include <Core/Time.hpp>
#include <Core/Buffer.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Render : public Component {
	public:
		Render( std::vector<tinyobj::shape_t> shapes ) : _shapes( shapes ), _indices( 0 ), Component( RENDERABLE ) { };
		virtual ~Render( ) { };

		void bind(Buffer& vertexBuffer, Buffer& indexBuffer, GLuint shaderID);

		void unbind( );

		size_t GetIndices( ) { return _indices; }


		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		std::vector<tinyobj::shape_t> getShapes( ) { return _shapes; };

		void ScaleTexture( float scale );
		void ScaleTexture( glm::vec2 scale );
		void ScaleTexture( float x, float y );
	private:
		std::vector<tinyobj::shape_t> _shapes;

		size_t _vertices;
		size_t _uvs;
		size_t _normals;
		size_t _indices;
	};
};
#endif
