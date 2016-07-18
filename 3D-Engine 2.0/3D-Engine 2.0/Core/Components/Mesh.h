#ifndef Engine_Mesh_h
#define Engine_Mesh_h

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GLM/glm.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>

//#include <Core/Components/Texture.hpp>

namespace Engine
{

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
	glm::mat4 BoneOffset;
	glm::mat4 mOffsetMatrix;
	glm::mat4 FinalTransformation;
};

struct VertexBoneData
{
	unsigned IDs[NUM_BONES_PER_VEREX];
	float Weights[NUM_BONES_PER_VEREX];

	void AddBoneData(unsigned BoneID, float Weight);
};

#define INVALID_MATERIAL 0xFFFFFFFF

	class Mesh : public VertexBoneData
	{
	public:
		Mesh();
		Mesh(const aiMatrix4x4& AssimpMatrix)
		{
			m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = AssimpMatrix.a4;
			m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = AssimpMatrix.b4;
			m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = AssimpMatrix.c4;
			m[3][0] = AssimpMatrix.d1; m[3][1] = AssimpMatrix.d2; m[3][2] = AssimpMatrix.d3; m[3][3] = AssimpMatrix.d4;
		}
		Mesh(const aiMatrix3x3& AssimpMatrix)
		{
			m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = 0.0f;
			m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = 0.0f;
			m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		~Mesh();

		//bool LoadMesh(const std::string& Filename, bool WithAdjacencies);

		void Render() {};

		bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		void InitMesh(unsigned Index, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones);
		//bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		//void Clear();
		void LoadBones(unsigned MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);
		
		glm::mat4 BoneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms);
		void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4 ParentTransform);
		void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedScaling(aiVector3D Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string Nodename);
		void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
		void InitTranslationTransform(float x, float y, float z);
		void setGlobalInverseTransform(glm::mat4 git) { m_GlobalInverseTransform = glm::inverse(git); }
	private:
		glm::mat4 m;
		glm::mat4 m_GlobalInverseTransform;
		glm::mat4 ScalingM;
		glm::mat4 RotationM;
		glm::mat4 TranslationM;
		glm::mat4 NodeTransformation;
		//bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		//void InitMesh(unsigned int Index, const aiMesh* paiMesh);
		//bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		//void Clear();

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
		//Mesh m_GlobalInverseTransform;
		//Mesh ScalingM;
		//Mesh RotationM;
		//Mesh TranslationM;
		//Mesh NodeTransformation;
		
	};
}
#endif
