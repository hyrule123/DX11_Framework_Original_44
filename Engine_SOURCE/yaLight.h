#pragma once
#include "yaComponent.h"
#include "yaGraphics.h"
#include "yaMesh.h"

namespace ya
{
	using namespace graphics;
	class Light : public Component
	{
	public:
		Light();
		~Light();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		void SetType(eLightType type);

		graphics::LightAttribute GetLightAttribute() { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		void SetSpecular(Vector4 spec) { mAttribute.specular = spec; }
		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }
		Vector4 GetDiffuse() { mAttribute.diffuse; }
		eLightType GetType() { return (eLightType)mAttribute.type; }
		float GetRadius() { mAttribute.radius; }
		float GetAngle() { mAttribute.angle; }
		

	private:
		graphics::LightAttribute mAttribute;
		std::shared_ptr<Mesh> mVolumeMesh; // ������ ������ ǥ���ϴ� �޽�
	};
}
