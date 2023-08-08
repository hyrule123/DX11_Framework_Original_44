#pragma once
#include "yaResource.h"
#include "yaShader.h"
#include "yaTexture.h"
#include "yaRenderer.h"
//#include "yaConstantBuffer.h"

using namespace ya::renderer;
namespace ya::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(eTextureSlot slot, std::shared_ptr<Texture> texture) { mTexture[(UINT)slot] = texture; }
		std::shared_ptr<Texture> GetTexture(eTextureSlot slot) { return mTexture[(UINT)slot]; }

		eRenderingMode GetRenderingMode() { return mMode; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }

		void SetMaterialCoefficient(Vector4 _vDiff, Vector4 _vSpec, Vector4 _vAmb, Vector4 _vEmis)
		{
			mDiffuseColor = _vDiff;
			mSpecularColor = _vSpec;
			mAmbientColor = _vAmb;
			mEmissiveColor = _vEmis;
		}

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture[(UINT)eTextureSlot::End];
		MaterialCB mCB;
		eRenderingMode mMode;

		Vector4 mDiffuseColor;
		Vector4 mSpecularColor;
		Vector4 mAmbientColor;
		Vector4 mEmissiveColor;
	};
}

