//#include <Core/Components/Mesh.h>
//
//
//
//void Engine::Mesh::VertexBoneData::AddBoneData(unsigned BoneID, float Weight)
//{
//	for (unsigned i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++)
//	{
//		if (Weights[i] == 0.0)
//		{
//			IDs[i] = BoneID;
//			Weights[i] = Weight;
//			return;
//		}
//	}
//	assert(0);
//}
//
//Engine::Mesh::Mesh()
//{
//
//}
//
//Engine::Mesh::~Mesh()
//{
//
//}
//
//bool Engine::Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
//{
//	std::vector<VertexBoneData> Bones;
//	unsigned NumVertices = 0;
//
//	m_Entries.resize(pScene->mNumMeshes);
//
//	//m_Textures.resize(pScene->mNumMaterials);
//
//	for (unsigned i = 0; i < m_Entries.size(); i++)
//	{
//		const aiMesh* paiMesh = pScene->mMeshes[i];
//		InitMesh(i, paiMesh);
//
//		NumVertices += pScene->mMeshes[i]->mNumVertices;
//	}
//
//	Bones.resize(NumVertices);
//
//	//TODO opengl code
//
//	//return InitMaterials(pScene, Filename);
//	return 0;
//}
//
//void Engine::Mesh::InitMesh(unsigned Index, const aiMesh* paiMesh)
//{
//	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;
//
//	std::vector<Vertex> Vertices;
//	std::vector<unsigned> Indices;
//
//	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
//	
//	for (unsigned i = 0; i < paiMesh->mNumVertices; i++)
//	{
//		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
//		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
//		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
//		const aiVector3D* pTangent = &(paiMesh->mTangents[i]);
//
//		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
//			glm::vec2(pTexCoord->x, pTexCoord->y),
//			glm::vec3(pNormal->x, pNormal->y, pNormal->z),
//			glm::vec3(pTangent->x, pTangent->y, pTangent->z));
//
//		Vertices.push_back(v);
//	}
//
//	for (unsigned i = 0; i < paiMesh->mNumFaces; i++)
//	{
//		const aiFace& Face = paiMesh->mFaces[i];
//		assert(Face.mNumIndices == 3);
//		Indices.push_back(Face.mIndices[0]);
//		Indices.push_back(Face.mIndices[1]);
//		Indices.push_back(Face.mIndices[2]);
//	}
//
//	m_Entries[Index].Init(Vertices, Indices);
//}
//
////bool Engine::Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
////{
////	std::string::size_type SlahsIndex = Filename.find_last_of("/");
////	std::string Dir;
////
////	if (SlahsIndex == std::string::npos)
////	{
////		Dir = ".";
////	}
////	else if (SlahsIndex == 0)
////	{
////		Dir = "/";
////	}
////	else
////	{
////		Dir = Filename.substr(0, SlahsIndex);
////	}
////
////	for (unsigned i = 0; i < pScene->mNumMaterials; i++)
////	{
////		const aiMaterial* pMaterial = pScene->mMaterials[i];
////
////		m_Textures[i] = NULL;
////		
////		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
////		{
////			aiString Path;
////			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
////			{
////				std::string FullPath = Dir + "/" + Path.data;
////				m_Textures[i] = new Engine::Texture(GL_TEXTURE_2D, FullPath.c_str());
////
////				if (!m_Textures[i]->Load())
////				{
////					printf("Error loading texture '%s'\n", FullPath.c_str());
////					delete m_Textures[i];
////					m_Textures[i] = NULL;
////					Ret = false;
////				}
////			}
////		}
////		if (!m_Textures[i])
////		{
////			m_Textures[i] = new Engine::Texture(GL_TEXTURE_2D, "../Content/white.png");
////			Ret = m_Textures[i]->Load();
////		}
////	}
////	return Ret;
////}
//
////void Engine::Mesh::Render()
////{
////	glEnableVertexAttribArray(0);
////	glEnableVertexAttribArray(1);
////	glEnableVertexAttribArray(2);
////
////	for (unsigned i = 0; i < m_Entries.size(); i++)
////	{
////		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
////		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
////		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
////		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
////
////		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
////		
////		const unsigned MaterialIndex = m_Entries[i].MaterialIndex;
////
////		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
////		{
////			m_Textures[MaterialIndex]->Bind();
////		}
////
////		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
////	}
////
////	glDisableVertexAttribArray(0);
////	glDisableVertexAttribArray(1);
////	glDisableVertexAttribArray(2);
////}
//
//void Engine::Mesh::LoadBones(unsigned MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
//{
//	for (unsigned i = 0; i < pMesh->mNumBones; i++)
//	{
//		unsigned BoneIndex = 0;
//		std::string BoneName(pMesh->mBones[i]->mName.data);
//
//		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end())
//		{
//			BoneIndex = m_NumBones;
//			m_NumBones++;
//			BoneInfo bi;
//			m_BoneInfo.push_back(bi);
//		}
//		else
//		{
//			BoneIndex = m_BoneMapping[BoneName];
//		}
//
//		m_BoneMapping[BoneName] = BoneIndex;
//		m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
//
//		for (unsigned j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
//		{
//			unsigned VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
//			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
//			Bones[VertexID].AddBoneData(BoneIndex, Weight);
//		}
//	}
//}
//
//glm::mat4 Engine::Mesh::BoneTransform(float TimeInSeconds, std::vector<aiMatrix4x4>& Transforms)
//{
//	glm::mat4 Identity;
//	Identity.InitIdentity();
//
//	float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
//	float TimeInTicks = TimeInSeconds *TicksPerSecond;
//	float AnimationTime = fmod(TimeInTicks, m_pScene->mAnimations[0]->mDuration);
//
//	ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);
//
//	Transforms.resize(m_NumBones);
//
//	for (unsigned i = 0; i < m_NumBones; i++)
//	{
//		Transforms[i] = m_BoneInfo[i].FinalTransformation;
//	}
//}
//
//void Engine::Mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform)
//{
//	std::string NodeName(pNode->mName.data);
//
//	const aiAnimation* pAnimation = m_pScene->mAnimations[0];
//	
//	aiMatrix4x4 NodeTransformation(pNode->mTransformation);
//	
//	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
//
//	if (pNodeAnim)
//	{
//		aiVector3D Scaling;
//		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
//		glm::mat4 ScalingM;
//		ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);
//
//		aiQuaternion RotationQ;
//		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
//		glm::mat4 RotationM = glm::mat4(RotationQ.GetMatrix());
//
//		aiVector3D Translation;
//		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
//		glm::mat4 TranslationM;
//		TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);
//
//		NodeTransformation = TranslationM * RotationM * ScalingM;
//	}
//
//	aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;
//
//	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end())
//	{
//		unsigned BoneIndex = m_BoneMapping[NodeName];
//		m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
//	}
//
//	for (unsigned i = 0; i < pNode->mNumChildren; i++)
//	{
//		ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
//	}
//}
//
//unsigned Engine::Mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	assert(pNodeAnim->mNumRotationKeys > 0);
//
//	for (unsigned i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
//	{
//		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
//		{
//			return i;
//		}
//	}
//
//	assert(0);
//}
//
//void Engine::Mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	if (pNodeAnim->mNumRotationKeys == 1)
//	{
//		Out = pNodeAnim->mRotationKeys[0].mValue;
//		return;
//	}
//
//	unsigned RotationIndex = FindRotation(AnimationTime, pNodeAnim);
//	unsigned NextRotationIndex = (RotationIndex + 1);
//	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
//	float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
//	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
//	assert(Factor >= 0.0f && Factor <= 1.0f);
//	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
//	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
//	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
//	Out = Out.Normalize();
//}
//
//unsigned Engine::Mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	assert(pNodeAnim->mNumScalingKeys > 0);
//
//	for (unsigned i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
//	{
//		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
//		{
//			return i;
//		}
//	}
//	assert(0);
//
//	return 0;
//}
//
//void Engine::Mesh::CalcInterpolatedScaling(aiVector3D Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	if (pNodeAnim->mNumScalingKeys == 1)
//	{
//		Out = pNodeAnim->mScalingKeys[0].mValue;
//		return;
//	}
//	//write findscaling!!!!
//	unsigned ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
//	unsigned NextScalingIndex = (ScalingIndex + 1);
//	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
//	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
//	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
//	assert(Factor >= 0.0f && Factor <= 1.0f);
//	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
//	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
//	aiVector3D Delta = End - Start;
//	Out = Start + Factor * Delta;
//}
//
//const aiNodeAnim* Engine::Mesh::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
//{
//	for (unsigned i = 0; i < pAnimation->mNumChannels; i++)
//	{
//		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
//
//		if (std::string(pNodeAnim->mNodeName.data) == NodeName)
//		{
//			return pNodeAnim;
//		}
//	}
//	return NULL;
//}