#include <Core/Components/Mesh.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

namespace Engine {

	void VertexBoneData::AddBoneData(unsigned BoneID, float Weight)
	{
		for (unsigned i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++)
		{
			if (Weights[i] == 0.0)
			{
				IDs[i] = BoneID;
				Weights[i] = Weight;
				return;
			}
		}
		assert(0);
	}

	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{

	}

	//bool Mesh::LoadMesh(const std::string& Filename, bool WithAjacencies)
	//{
	//	m_withAdjacencies = WithAjacencies;
	//
	//	Clear();
	//
	//	glGenVertexArrays(1, &m_VAO);
	//	glBindVertexArray(m_VAO);
	//
	//	glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffes);
	//
	//	bool Ret = false;
	//
	//	m_pScene = m_Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate |
	//													 aiProcess_GenSmoothNormals |
	//													 aiProcess_FlipUVs |
	//													 aiProcess_JoinIdenticalVertices);
	//
	//	if (m_pScene) {
	//		m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
	//		m_GlobalInverseTransform.Inverse();
	//		Ret = InitFromScene(m_pScene, Filename);
	//	}
	//	else {
	//		std::cout << "Error parsing '%s': '%s* \n" << Filename.c_str(), m_Importer.GetErrorString());
	//	}
	//
	//	glBindVertexArray(0);
	//
	//	return Ret;
	//}

	bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
	{
		std::vector<VertexBoneData> Bones;
		unsigned NumVertices = 0;

		m_Entries.resize(pScene->mNumMeshes);

		//m_Textures.resize(pScene->mNumMaterials);

		for (unsigned i = 0; i < m_Entries.size(); i++)
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			InitMesh(i, paiMesh, Bones);

			NumVertices += pScene->mMeshes[i]->mNumVertices;
		}

		Bones.resize(NumVertices);

		//TODO opengl code

		//return InitMaterials(pScene, Filename);
		return 0;
	}

	void Mesh::InitMesh(unsigned Index, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones)
	{
		m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

		std::vector<Vertex> Vertices;
		std::vector<unsigned> Indices;

		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		for (unsigned i = 0; i < paiMesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
			const aiVector3D* pTangent = &(paiMesh->mTangents[i]);

			Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z),
				glm::vec3(pTangent->x, pTangent->y, pTangent->z));

			Vertices.push_back(v);
		}

		LoadBones(Index, paiMesh, Bones);

		for (unsigned i = 0; i < paiMesh->mNumFaces; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
		}

		m_Entries[Index].Init(Vertices, Indices);
	}

	//bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
	//{
	//	std::string::size_type SlahsIndex = Filename.find_last_of("/");
	//	std::string Dir;
	//
	//	if (SlahsIndex == std::string::npos)
	//	{
	//		Dir = ".";
	//	}
	//	else if (SlahsIndex == 0)
	//	{
	//		Dir = "/";
	//	}
	//	else
	//	{
	//		Dir = Filename.substr(0, SlahsIndex);
	//	}
	//
	//	for (unsigned i = 0; i < pScene->mNumMaterials; i++)
	//	{
	//		const aiMaterial* pMaterial = pScene->mMaterials[i];
	//
	//		m_Textures[i] = NULL;
	//		
	//		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	//		{
	//			aiString Path;
	//			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
	//			{
	//				std::string FullPath = Dir + "/" + Path.data;
	//				m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());
	//
	//				if (!m_Textures[i]->Load())
	//				{
	//					printf("Error loading texture '%s'\n", FullPath.c_str());
	//					delete m_Textures[i];
	//					m_Textures[i] = NULL;
	//					Ret = false;
	//				}
	//			}
	//		}
	//		if (!m_Textures[i])
	//		{
	//			m_Textures[i] = new Texture(GL_TEXTURE_2D, "../Content/white.png");
	//			Ret = m_Textures[i]->Load();
	//		}
	//	}
	//	return Ret;
	//}

	//void Mesh::Render()
	//{
	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glEnableVertexAttribArray(2);
	//
	//	for (unsigned i = 0; i < m_Entries.size(); i++)
	//	{
	//		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
	//
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
	//		
	//		const unsigned MaterialIndex = m_Entries[i].MaterialIndex;
	//
	//		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
	//		{
	//			m_Textures[MaterialIndex]->Bind();
	//		}
	//
	//		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	//	}
	//
	//	glDisableVertexAttribArray(0);
	//	glDisableVertexAttribArray(1);
	//	glDisableVertexAttribArray(2);
	//}

	void Mesh::LoadBones(unsigned MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
	{
		for (unsigned i = 0; i < pMesh->mNumBones; i++)
		{
			unsigned BoneIndex = 0;
			std::string BoneName(pMesh->mBones[i]->mName.data);

			if (m_BoneMapping.find(BoneName) == m_BoneMapping.end())
			{
				BoneIndex = m_NumBones;
				m_NumBones++;
				BoneInfo bi;
				m_BoneInfo.push_back(bi);
			}
			else
			{
				BoneIndex = m_BoneMapping[BoneName];
			}

			m_BoneMapping[BoneName] = BoneIndex;
			m_BoneInfo[BoneIndex].BoneOffset = glm::mat4(glm::vec4(pMesh->mBones[i]->mOffsetMatrix.a1, pMesh->mBones[i]->mOffsetMatrix.a2, pMesh->mBones[i]->mOffsetMatrix.a3, pMesh->mBones[i]->mOffsetMatrix.a4),
				glm::vec4(pMesh->mBones[i]->mOffsetMatrix.b1, pMesh->mBones[i]->mOffsetMatrix.b2, pMesh->mBones[i]->mOffsetMatrix.b3, pMesh->mBones[i]->mOffsetMatrix.b4),
				glm::vec4(pMesh->mBones[i]->mOffsetMatrix.c1, pMesh->mBones[i]->mOffsetMatrix.c2, pMesh->mBones[i]->mOffsetMatrix.c3, pMesh->mBones[i]->mOffsetMatrix.c4),
				glm::vec4(pMesh->mBones[i]->mOffsetMatrix.d1, pMesh->mBones[i]->mOffsetMatrix.d2, pMesh->mBones[i]->mOffsetMatrix.d3, pMesh->mBones[i]->mOffsetMatrix.d4));

			for (unsigned j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
			{
				unsigned VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
				float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
				Bones[VertexID].AddBoneData(BoneIndex, Weight);
			}
		}
	}

	glm::mat4 Mesh::BoneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms)
	{
		glm::mat4 Identity = glm::mat4(1.0f);

		float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
		float TimeInTicks = TimeInSeconds *TicksPerSecond;
		float AnimationTime = fmod(TimeInTicks, m_pScene->mAnimations[0]->mDuration);

		ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);

		Transforms.resize(m_NumBones);

		for (unsigned i = 0; i < m_NumBones; i++)
		{
			Transforms[i] = m_BoneInfo[i].FinalTransformation;
		}
		return Identity;
	}

	void Mesh::InitTranslationTransform(float x, float y, float z)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	void Mesh::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
	{
		m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
		m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
		m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
		m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
	}

	void Mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4 ParentTransform)
	{
		std::string NodeName(pNode->mName.data);

		const aiAnimation* pAnimation = m_pScene->mAnimations[0];

		/*Mesh */NodeTransformation = glm::mat4(glm::vec4(pNode->mTransformation.a1, pNode->mTransformation.a2, pNode->mTransformation.a3, pNode->mTransformation.a4),
			glm::vec4(pNode->mTransformation.b1, pNode->mTransformation.b2, pNode->mTransformation.b3, pNode->mTransformation.b4),
			glm::vec4(pNode->mTransformation.c1, pNode->mTransformation.c2, pNode->mTransformation.c3, pNode->mTransformation.c4),
			glm::vec4(pNode->mTransformation.d1, pNode->mTransformation.d2, pNode->mTransformation.d3, pNode->mTransformation.d4));

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

		if (pNodeAnim)
		{
			aiVector3D Scaling;
			CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			/*Mesh ScalingM;*/
			ScalingM = glm::mat4(glm::vec4(Scaling.x, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, Scaling.y, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, Scaling.z, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			aiQuaternion RotationQ;
			CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
			/*Mesh*/ RotationM = glm::mat4(glm::vec4(RotationQ.GetMatrix().a1, RotationQ.GetMatrix().a2, RotationQ.GetMatrix().a3, 0.0f),
				glm::vec4(RotationQ.GetMatrix().b1, RotationQ.GetMatrix().b2, RotationQ.GetMatrix().b3, 0.0f),
				glm::vec4(RotationQ.GetMatrix().c1, RotationQ.GetMatrix().c2, RotationQ.GetMatrix().c3, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

			aiVector3D Translation;
			CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
			/*Mesh TranslationM;*/
			TranslationM = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, Translation.x),
				glm::vec4(0.0f, 1.0f, 0.0f, Translation.y),
				glm::vec4(0.0f, 0.0f, 1.0f, Translation.z),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			//InitTranslationTransform(Translation.x, Translation.y, Translation.z);

			NodeTransformation = TranslationM * RotationM * ScalingM;
		}

		glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

		if (m_BoneMapping.find(NodeName) != m_BoneMapping.end())
		{
			unsigned BoneIndex = m_BoneMapping[NodeName];
			m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
		}

		for (unsigned i = 0; i < pNode->mNumChildren; i++)
		{
			ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
		}
	}

	unsigned Mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumRotationKeys > 0);

		for (unsigned i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
			{
				return i;
			}
		}

		assert(0);
	}

	void Mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumRotationKeys == 1)
		{
			Out = pNodeAnim->mRotationKeys[0].mValue;
			return;
		}

		unsigned RotationIndex = FindRotation(AnimationTime, pNodeAnim);
		unsigned NextRotationIndex = (RotationIndex + 1);
		assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
		float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
		float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
		aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
		Out = Out.Normalize();
	}

	unsigned Mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumScalingKeys > 0);

		for (unsigned i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
			{
				return i;
			}
		}
		assert(0);

		return 0;
	}

	void Mesh::CalcInterpolatedScaling(aiVector3D Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumScalingKeys == 1)
		{
			Out = pNodeAnim->mScalingKeys[0].mValue;
			return;
		}
		//write findscaling!!!!
		unsigned ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
		unsigned NextScalingIndex = (ScalingIndex + 1);
		assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
		float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
		const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

	const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
	{
		for (unsigned i = 0; i < pAnimation->mNumChannels; i++)
		{
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

			if (std::string(pNodeAnim->mNodeName.data) == NodeName)
			{
				return pNodeAnim;
			}
		}
		return NULL;
	}

	unsigned Mesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		for (unsigned i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
			{
				return i;
			}
		}

		assert(0);

		return 0;
	}

	void Mesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumPositionKeys == 1)
		{
			Out = pNodeAnim->mPositionKeys[0].mValue;
			return;
		}

		unsigned PositionIndex = FindPosition(AnimationTime, pNodeAnim);
		unsigned NextPositionIndex = (PositionIndex + 1);
		assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
		float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}
}