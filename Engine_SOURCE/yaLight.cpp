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
			tr->SetScale(Vector3(mAttribute.radius * 2.f, mAttribute.radius * 2.f, mAttribute.radius * 2.f));
		}

		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 0.0f);
		
		renderer::PushLightAttribute(mAttribute);
	}

	void Light::Render()
	{
		std::shared_ptr<Material> material 
			= Resources::Find<Material>(L"LightMaterial");

		if (material == nullptr)
		{
			return;
		}

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
			mVolumeMesh = Resources::Find<Mesh>(L"CircleMesh");
		}
		else if (mAttribute.type == eLightType::Spot)
		{
			//
		}
	}
}
