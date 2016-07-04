#ifndef Mesh_h
#define Mesh_h
#include <GL\glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GLM/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <map>


#include <Core/Components/Texture.hpp>

struct Vertex
{
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;
	glm::vec3 m_tangent;

	Vertex() {};

	Vertex(const glm::vec3& pos,
		const glm::vec2& tex,
		const glm::vec3& normal,
		const glm::vec3& tangent)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
		m_tangent = tangent;
	}
};
#define NUM_BONES_PER_VEREX 4

struct BoneInfo
{
	aiMatrix4x4 BoneOffset;
	aiMatrix4x4 mOffsetMatrix;
	aiMatrix4x4 FinalTransformation;
};

struct VertexBoneData
{
	unsigned IDs[NUM_BONES_PER_VEREX];
	float Weights[NUM_BONES_PER_VEREX];

	void AddBoneData(unsigned BoneID, float Weight);
};

namespace Engine
{
	class Mesh : public VertexBoneData
	{
	public:
		Mesh();

		~Mesh();

		bool LoadMesh(const std::string& Filename) { return 1; };

		void Render() {};

		bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		void InitMesh(unsigned int Index, const aiMesh* paiMesh);
		//bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		//void Clear();
		void LoadBones(unsigned MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);
		void VertexBoneData::AddBoneData(unsigned BoneID, float Weight);
		glm::mat4 BoneTransform(float TimeInSeconds, std::vector<aiMatrix4x4>& Transforms);
		void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform);
		void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedScaling(aiVector3D Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string Nodename);

	private:
		//bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		//void InitMesh(unsigned int Index, const aiMesh* paiMesh);
		//bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		//void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

		struct MeshEntry {
			MeshEntry() {};
			~MeshEntry() {};

			bool Init(const std::vector<Vertex>& Vertices,
				const std::vector<unsigned>& Indices) {
				return 1;
			};

			GLuint VB;
			GLuint IB;
			unsigned NumIndices;
			unsigned MaterialIndex;
			unsigned BaseVertex;
		};
		std::map<std::string, unsigned> m_BoneMapping;
		std::vector<BoneInfo> m_BoneInfo;
		std::vector<MeshEntry> m_Entries;
		unsigned m_NumBones;
		//std::vector<Engine::Texture*> m_Textures;
		bool Ret;
		const aiScene* m_pScene;
		glm::mat4 m_GlobalInverseTransform;
		
	};
}
#endif
