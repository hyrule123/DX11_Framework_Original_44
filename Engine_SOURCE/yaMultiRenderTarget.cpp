#include "yaMultiRenderTarget.h"


namespace ya::graphics
{



	MultiRenderTarget::MultiRenderTarget()
		: mRenderTargets{}
		, mDSTexture(nullptr)
		, mRTCount(0)
	{

	}

	MultiRenderTarget::~MultiRenderTarget()
	{
	}

	void MultiRenderTarget::Create(std::shared_ptr<Texture> texture[8]
		, std::shared_ptr<Texture> dsTexture)
	{
		for (size_t i = 0; i < 8; i++)
		{
			if (texture[i].get() == nullptr)
			{
				mRTCount = i;
				break;
			}

			mRenderTargets[i] = texture[i];
		}

		mDSTexture = dsTexture;
	}

	void MultiRenderTarget::OmSetRenderTarget()
	{
		ID3D11RenderTargetView* arrRTV[8] = {};
		for (size_t i = 0; i < 8; i++)
		{
			if (mRenderTargets[i])
			{
				arrRTV[i] = mRenderTargets[i]->GetRTV().Get();
			}
		}

		if (mDSTexture.get() != nullptr)
		{
			GetDevice()->OMSetRenderTarget(mRTCount, arrRTV, mDSTexture->GetDSV().Get());
		}
		else
		{
			GetDevice()->OMSetRenderTarget(mRTCount, arrRTV, nullptr);
		}
	}

}
