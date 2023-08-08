#pragma once
#include "yaResource.h"
#include "yaMaterial.h"
#include "yaMesh.h"


namespace ya
{
	class MeshData : public Resource
	{
	public:
		MeshData();
		~MeshData();

		static MeshData* LoadFromFbx(const std::wstring& path);

		virtual void Save(const std::wstring& path);
		virtual HRESULT Load(const std::wstring& path) { return S_OK; }

		GameObject* Instantiate();


	private:
		std::shared_ptr<Mesh> mMesh;
		std::vector<std::shared_ptr<Material>> mMaterials;
	};
}
