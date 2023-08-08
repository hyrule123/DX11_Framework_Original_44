#pragma once
#include "yaEngine.h"
#include "yaMath.h"
#include "yaGraphics.h"

#include <fbxsdk/scene/geometry/fbxnurbs.h >
#include <fbxsdk.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\fbx\\lib\\Debug\\libfbxsdk-md.lib") 
#else 
#pragma comment(lib, "..\\External\\fbx\\lib\\Release\\libfbxsdk-md.lib") 
#endif

//#ifdef _DEBUG
//#pragma comment(lib, "..\\External\\fbx\\lib\\Debug\\libxml2-md.lib") 
//#else 
//#pragma comment(lib, "..\\External\\fbx\\lib\\Release\\libxml2-md.lib") 
//#endif

namespace ya
{
	using namespace math;
	using namespace graphics;

	struct FbxMaterial
	{
		MaterialColr color;

		std::wstring name;
		std::wstring diffuse;
		std::wstring normal;
		std::wstring specular;
	};

	struct WeightAndIndices
	{
		int boneIdx;
		double weight;
	};

	struct Container
	{
		std::wstring name;
		std::vector<Vector3> positions;
		std::vector<Vector3> tangents;
		std::vector<Vector3> binormals;
		std::vector<Vector3> normals;
		std::vector<Vector2> uv;

		std::vector<std::vector<UINT>> indices;
		std::vector<FbxMaterial> materials;

		bool bAnimation;
		std::vector<std::vector<WeightAndIndices>> weightAndIndices;
		std::vector<Vector4> skiningWeights;
		std::vector<Vector4> skiningIndices;

		void Resize(UINT size)
		{
			positions.resize(size);
			tangents.resize(size);
			binormals.resize(size);
			normals.resize(size);
			uv.resize(size);
			indices.resize(size);
			materials.resize(size);
			weightAndIndices.resize(size);
		}
	};

	struct KeyFrame
	{
		fbxsdk::FbxAMatrix transform;
		double time;
	};

	struct Bone
	{
		std::wstring name;
		int depth;		//°èÃþ±¸Á¶ ±íÀÌ
		int parentIdx; //ºÎ¸ðÀÇ º» ÀÎµ¦½º
		fbxsdk::FbxAMatrix offsetMatrix; // ³ª --> ºÎ¸ð --> »Ñ¸® --> local
		fbxsdk::FbxAMatrix boneMatrix;
		std::vector<KeyFrame> keyFrames;
	};

	struct AnimationClip
	{
		std::wstring name;
		fbxsdk::FbxTime startTime;
		fbxsdk::FbxTime endTime;
		fbxsdk::FbxLongLong timeLength;
		fbxsdk::FbxTime::EMode mode;
	};


	class FbxLoader
	{
	public:
		static void Initialize();
		static bool  LoadFbx(const std::wstring& path);
		static void LoadMeshDataFromNode(fbxsdk::FbxNode* node);
		static void LoadMesh(fbxsdk::FbxMesh* _pFbxMesh);
		static void LoadMaterial(fbxsdk::FbxSurfaceMaterial* _pMtrlSur);

		static void GetTangent(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder);
		static void GetBinormal(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder);
		static void GetNormal(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iVtxOrder);
		static void GetUV(fbxsdk::FbxMesh* _pMesh, Container* _pContainer, int _iIdx, int _iUVIndex);

		static Vector4 GetMtrlData(fbxsdk::FbxSurfaceMaterial* _pSurface, const char* _pMtrlName, const char* _pMtrlFactorName);
		static std::wstring GetMtrlTextureName(fbxsdk::FbxSurfaceMaterial* _pSurface, const char* _pMtrlProperty);

		static void LoadTexture();
		static void CreateMaterial();

		// Animation
		static void LoadSkeleton(fbxsdk::FbxNode* _pNode);
		static void LoadSkeleton_Re(fbxsdk::FbxNode* _pNode, int _iDepth, int _iIdx, int _iParentIdx);
		static void LoadAnimationClip();
		static void Triangulate(fbxsdk::FbxNode* _pNode);

		static void LoadAnimationData(fbxsdk::FbxMesh* _pMesh, Container* _pContainer);
		static void CheckWeightAndIndices(fbxsdk::FbxMesh* _pMesh, Container* _pContainer);
		static void LoadWeightsAndIndices(fbxsdk::FbxCluster* _pCluster, int _iBoneIdx, Container* _pContainer);
		static void LoadOffsetMatrix(fbxsdk::FbxCluster* _pCluster, const fbxsdk::FbxAMatrix& _matNodeTransform, int _iBoneIdx, Container* _pContainer);
		static void LoadKeyframeTransform(fbxsdk::FbxNode* _pNode, fbxsdk::FbxCluster* _pCluster, const fbxsdk::FbxAMatrix& _matNodeTransform
			, int _iBoneIdx, Container* _pContainer);
		static int FindBoneIndex(std::string _strBoneName);
		static fbxsdk::FbxAMatrix GetTransform(fbxsdk::FbxNode* _pNode);

		static void Release();
		
		static int GetContainerCount() { return (int)mContainers.size(); }
		static const Container& GetContainer(int idx) { return mContainers[idx]; }
		static std::vector<Bone*>& GetBones() { return mBones; }
		static std::vector<AnimationClip*>& GetAnimClip() { return mAnimationClips; }


	private:
		static fbxsdk::FbxManager* mManager;
		static fbxsdk::FbxScene* mScene;
		static fbxsdk::FbxImporter* mImporter;

		static std::vector<Container> mContainers;

		//Animation
		static std::vector<Bone*> mBones;
		static fbxsdk::FbxArray<fbxsdk::FbxString*> mAnimationNames;
		static std::vector<AnimationClip*> mAnimationClips;
	};
}
