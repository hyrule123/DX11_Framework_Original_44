#include "yaMesh.h"
#include "yaRenderer.h"
#include "yaGraphicDevice_DX11.h"
#include "yaFbxLoader.h"
#include "yaMesh.h"

namespace ya
{
	Mesh::Mesh()
		: Resource(eResourceType::Mesh)
		, mVBDesc{}
		, mIndexInfos{}
	{

	}

	Mesh::~Mesh()
	{

	}

	std::shared_ptr<Mesh> Mesh::CreateFromContainer(FbxLoader* loader)
	{
		const Container& container = loader->GetContainer(0);

		UINT iVtxCount = (UINT)container.positions.size();
		D3D11_BUFFER_DESC tVtxDesc = {};

		tVtxDesc.ByteWidth = sizeof(graphics::Vertex) * iVtxCount;
		tVtxDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		tVtxDesc.Usage = D3D11_USAGE_DEFAULT;
		if (D3D11_USAGE_DYNAMIC == tVtxDesc.Usage)
			tVtxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA tSub = {};
		tSub.pSysMem = malloc(tVtxDesc.ByteWidth);

		graphics::Vertex* pSys = (graphics::Vertex*)tSub.pSysMem;
		for (UINT i = 0; i < iVtxCount; ++i)
		{
			pSys[i].pos = Vector4(container.positions[i].x
								, container.positions[i].y
								, container.positions[i].z, 1.0f);
			pSys[i].uv = container.uv[i];
			pSys[i].color = Vector4(1.f, 0.f, 1.f, 1.f);
			pSys[i].normal = container.normals[i];
			pSys[i].tangent= container.tangents[i];
			pSys[i].biNormal = container.binormals[i];
			//pSys[i].vWeights = container->vecWeights[i];
			//pSys[i].vIndices = container->vecIndices[i];
		}

		Microsoft::WRL::ComPtr<ID3D11Buffer> pVB = NULL;
		if (FAILED(GetDevice()->CreateBuffer(&tVtxDesc, &tSub, pVB.GetAddressOf())))
		{
			return NULL;
		}

		std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>();
		pMesh->mVertexBuffer = pVB;
		pMesh->mVtxCount = iVtxCount;
		pMesh->mVBDesc= tVtxDesc;
		pMesh->pVtxSysMem = pSys;

		// 인덱스 정보
		UINT iIdxBufferCount = (UINT)container.indices.size();
		D3D11_BUFFER_DESC tIdxDesc = {};

		for (UINT i = 0; i < iIdxBufferCount; ++i)
		{
			tIdxDesc.ByteWidth = (UINT)container.indices[i].size() * sizeof(UINT); // Index Format 이 R32_UINT 이기 때문
			tIdxDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			tIdxDesc.Usage = D3D11_USAGE_DEFAULT;
			if (D3D11_USAGE_DYNAMIC == tIdxDesc.Usage)
				tIdxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			void* pSysMem = malloc(tIdxDesc.ByteWidth);
			memcpy(pSysMem, container.indices[i].data(), tIdxDesc.ByteWidth);
			tSub.pSysMem = pSysMem;

			Microsoft::WRL::ComPtr<ID3D11Buffer> pIB = nullptr;
			if (FAILED(GetDevice()->CreateBuffer(&tIdxDesc, &tSub, pIB.GetAddressOf())))
			{
				return NULL;
			}

			IndexInfo info = {};
			info.desc = tIdxDesc;
			info.indexCount = (UINT)container.indices[i].size();
			info.pIdxSysMem = pSysMem;
			info.buffer = pIB;

			pMesh->mIndexInfos.push_back(info);
		}

		return pMesh;
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT count)
	{
		// 버텍스 버퍼
		mVBDesc.ByteWidth = sizeof(graphics::Vertex) * count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.CPUAccessFlags = 0;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		mVBDesc.MiscFlags = 0;
		mVBDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf()))
			return false;

		pVtxSysMem = new graphics::Vertex[count];
		memcpy(pVtxSysMem, data, sizeof(graphics::Vertex) * count);

		return true;
	}

	bool Mesh::CreateIndexBuffer(void* data, UINT indexBufferCount)
	{
		IndexInfo indexInfo = {};
		indexInfo.indexCount = indexBufferCount;
		indexInfo.desc.ByteWidth = sizeof(UINT) * indexBufferCount;


		indexInfo.desc.CPUAccessFlags = 0;
		indexInfo.desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		indexInfo.desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexInfo.desc.MiscFlags = 0;
		indexInfo.desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!GetDevice()->CreateBuffer(&indexInfo.desc, &subData, indexInfo.buffer.GetAddressOf()))
			return false;

		indexInfo.pIdxSysMem = new UINT[indexInfo.indexCount];
		memcpy(indexInfo.pIdxSysMem, data, sizeof(UINT) * indexInfo.indexCount);
			
		mIndexInfos.push_back(indexInfo);
		return true;
	}

	void Mesh::BindBuffer(UINT subSet)
	{
		// Input Assembeler 단계에 버텍스버퍼 정보 지정
		UINT stride = sizeof(graphics::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		GetDevice()->BindIndexBuffer(mIndexInfos[subSet].buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void Mesh::Render(UINT subSet)
	{
		GetDevice()->DrawIndexed(mIndexInfos[subSet].indexCount, 0, 0);
	}
	
	void Mesh::RenderInstanced(UINT count, UINT subSet)
	{
		GetDevice()->DrawIndexedInstanced(mIndexInfos[subSet].indexCount, count, 0, 0, 0);
	}
}
