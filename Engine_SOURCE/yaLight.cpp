#include "yaLight.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"

namespace ya
{
	Light::Light()
		: Component(eComponentType::Light)
	{
		renderer::lights.push_back(this);
	}

	Light::~Light()
	{

	}

	void Light::Initalize()
	{

	}

	void Light::Update()
	{

	}

	void Light::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (eLightType::Point == mAttribute.type)
		{
			tr->SetScale(Vector3(mAttribute.radius * 5.f, mAttribute.radius * 5.f, mAttribute.radius * 5.f));
		}

		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 0.0f);

		renderer::PushLightAttribute(mAttribute);
	}

	void Light::Render()
	{

		std::shared_ptr<Material> material = nullptr;

		if (mAttribute.type == eLightType::Directional)
		{
			material = Resources::Find<Material>(L"LightMaterial");
		}
		else if (mAttribute.type == eLightType::Point)
		{
			material = Resources::Find<Material>(L"LightPointMaterial");
		}


		if (material == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetConstantBuffer();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		LightCB data = {};
		data.numberOfLight = renderer::lights.size();
		data.indexOfLight = mIndex;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

		mVolumeMesh->BindBuffer();
		material->Bind();
		mVolumeMesh->Render();
	}
	void Light::SetType(eLightType type)
	{
		mAttribute.type = type;
		if (mAttribute.type == eLightType::Directional)
		{
			mVolumeMesh = Resources::Find<Mesh>(L"RectMesh");
		}
		else if (mAttribute.type == eLightType::Point)
		{
			mVolumeMesh = Resources::Find<Mesh>(L"SphereMesh");
		}
		else if (mAttribute.type == eLightType::Spot)
		{
			//
		}
	}
}
