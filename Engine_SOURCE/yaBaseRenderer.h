#pragma once
#include "yaComponent.h"
#include "yaMesh.h"
#include "yaMaterial.h"

namespace ya
{
	class BaseRenderer : public Component
	{
	public:
		BaseRenderer(eComponentType type);
		virtual ~BaseRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override; 
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh); //{ mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader, int idx) { mMaterial[idx] = shader; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		std::shared_ptr <Material> GetMaterial(int idx) { return mMaterial[idx]; }

	private:
		std::shared_ptr <Mesh> mMesh;
		std::vector<std::shared_ptr <Material>> mMaterial;
	};
}
