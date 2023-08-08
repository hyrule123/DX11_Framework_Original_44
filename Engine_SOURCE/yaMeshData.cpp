#include "yaMeshData.h"
#include "yaGameObject.h"
#include "yaFbxLoader.h"
#include "yaResources.h"

namespace ya
{
	MeshData::MeshData()
		: Resource(eResourceType::MeshData)
	{
	}
	MeshData::~MeshData()
	{
	}
	MeshData* MeshData::LoadFromFbx(const std::wstring& path)
	{
		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring fullPath = parentPath.wstring() + L"\\Resources\\" + path;

		
		FbxLoader loader;
		loader.Initialize();
		loader.LoadFbx(fullPath);

		// 메시 가져오기
		std::shared_ptr<Mesh> mesh = nullptr;
		mesh = Mesh::CreateFromContainer(&loader);

		// 리소스에 넣어주기

		std::wstring name = std::filesystem::path(fullPath).stem();
		name += L".mesh";
		Resources::Insert(name, mesh);

		// 메테리얼 가져오기

		std::vector<std::shared_ptr<Material>> materials = {};
		for (size_t i = 0; i < loader.GetContainer(0).materials.size(); i++)
		{
			std::shared_ptr<Material> material
				= Resources::Find<Material>(loader.GetContainer(0).materials[i].name);

			materials.push_back(material);
		}

		MeshData* meshData = new MeshData();
		meshData->mMesh = mesh;
		meshData->mMaterials = materials;

		return meshData;
	}

	void MeshData::Save(const std::wstring& path)
	{
	}
	GameObject* MeshData::Instantiate()
	{
		//GameObject* gameObj = 

		return nullptr;
	}
}
