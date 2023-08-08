#include "yaFbxLoader.h"


namespace ya
{
	fbxsdk::FbxManager* FbxLoader::mManager = nullptr;
	fbxsdk::FbxScene* FbxLoader::mScene = nullptr;
	fbxsdk::FbxImporter* FbxLoader::mImporter = nullptr;
	std::vector<Container> FbxLoader::mContainers = {};
	std::vector<Bone*> FbxLoader::mBones = {};
	fbxsdk::FbxArray<fbxsdk::FbxString*> FbxLoader::mAnimationNames = {};
	std::vector<AnimationClip*> FbxLoader::mAnimationClips = {};

	void FbxLoader::LoadMeshDataFromNode(fbxsdk::FbxNode* _pRoot)
	{
	}
	void FbxLoader::LoadMesh(fbxsdk::FbxMesh* _pFbxMesh)
	{
	}
	void FbxLoader::LoadMaterial(fbxsdk::FbxSurfaceMaterial* _pMtrlSur)
	{
	}
	void FbxLoader::GetTangent(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder)
	{
	}
	void FbxLoader::GetBinormal(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder)
	{
	}
	void FbxLoader::GetNormal(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder)
	{
	}
	void FbxLoader::GetUV(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder)
	{
	}
	Vector4 FbxLoader::GetMtrlData(fbxsdk::FbxSurfaceMaterial* _pSurface, const char* _pMtrlName, const char* _pMtrlFactorName)
	{
		return Vector4();
	}
	std::wstring FbxLoader::GetMtrlTextureName(fbxsdk::FbxSurfaceMaterial* _pSurface, const char* _pMtrlProperty)
	{
		return std::wstring();
	}
	void FbxLoader::LoadTexture()
	{
	}
	void FbxLoader::CreateMaterial()
	{
	}
	void FbxLoader::LoadSkeleton(fbxsdk::FbxNode* _pNode)
	{
	}
	void FbxLoader::LoadSkeleton_Re(fbxsdk::FbxNode* _pNode, int _iDepth, int _iIdx, int _iParentIdx)
	{
	}
	void FbxLoader::LoadAnimationClip()
	{
	}
	void FbxLoader::Triangulate(fbxsdk::FbxNode* _pNode)
	{
	}
	void FbxLoader::LoadAnimationData(fbxsdk::FbxMesh* _pMesh, Container* _pContainer)
	{
	}
	void FbxLoader::LoadWeightsAndIndices(fbxsdk::FbxCluster* _pCluster, int _iBoneIdx, Container* _pContainer)
	{
	}
	void FbxLoader::LoadOffsetMatrix(fbxsdk::FbxCluster* _pCluster, const fbxsdk::FbxAMatrix& _matNodeTransform, int _iBoneIdx, Container* _pContainer)
	{
	}
	void FbxLoader::LoadKeyframeTransform(fbxsdk::FbxNode* _pNode, fbxsdk::FbxCluster* _pCluster, const fbxsdk::FbxAMatrix& _matNodeTransform, int _iBoneIdx, Container* _pContainer)
	{
	}
}
