#include "yaLight.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaRenderer.h"
#include "yaResources.h"

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
		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 0.0f);
		
		renderer::PushLightAttribute(mAttribute);
	}

	void Light::Render()
	{
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
