#include <Core/Components/Renderable.hpp>

namespace Engine {

	void Render::bind( Buffer& vertexBuffer, Buffer& indexBuffer, GLuint shaderID ) {
		
		std::vector<float> vertexVector;
		std::vector<float> uvVector;
		std::vector<float> normalVector;
		std::vector<size_t> indiceVector;

		for (int i = 0; i < _shapes.size(); i++)
		{
			vertexVector.insert(vertexVector.begin(), _shapes[i].mesh.positions.begin(), _shapes[i].mesh.positions.end());
			uvVector.insert(uvVector.begin(), _shapes[i].mesh.texcoords.begin(), _shapes[i].mesh.texcoords.end());
			normalVector.insert(normalVector.begin(), _shapes[i].mesh.normals.begin(), _shapes[i].mesh.normals.end());
			for (size_t ind : _shapes[i].mesh.indices) { ind += vertexVector.size(); }
			indiceVector.insert(indiceVector.begin(), _shapes[i].mesh.indices.begin(), _shapes[i].mesh.indices.end());
		}

		vertexVector.insert(vertexVector.begin(), uvVector.begin(), uvVector.end());
		vertexVector.insert(vertexVector.begin(), normalVector.begin(), normalVector.end());

		_indices = indiceVector.size();

		vertexBuffer.BindBufferData(vertexVector.size(), (void*)vertexVector.data());
		indexBuffer.BindBufferData(indiceVector.size(), (void*)indiceVector.data());

		GLint PositionLocation		= glGetAttribLocation(shaderID, "in_Position");
		GLint TexCoordinateLocation	= glGetAttribLocation(shaderID, "in_TexCoord");
		GLint NormalLocation		= glGetAttribLocation(shaderID, "in_Normal");

		if (PositionLocation != -1) {
			glEnableVertexAttribArray(PositionLocation);
			glVertexAttribPointer(PositionLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(GLfloat)));
		}; //if (PositionLocation != -1)

		if (TexCoordinateLocation != -1) {
			glEnableVertexAttribArray(TexCoordinateLocation);
			glVertexAttribPointer(TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
		}; //if (TexCoordinateLocation != -1)

		if (NormalLocation != -1) {
			glEnableVertexAttribArray(NormalLocation);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(GLfloat)));
		}; //if (NormalLocation != -1)
	}

	void Render::Init( ) { }

	void Render::Cleanup( ) { }
};