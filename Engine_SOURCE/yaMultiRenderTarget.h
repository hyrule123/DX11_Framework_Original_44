#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

namespace ya::graphics
{
	class MultiRenderTarget : public Entity
	{
	public:
		MultiRenderTarget();
		~MultiRenderTarget();

		void Create(std::shared_ptr<Texture> texture[8], std::shared_ptr<Texture> dsTexture);
		void OmSetRenderTarget();

	private:
		std::shared_ptr<Texture> mRenderTargets[8];
		std::shared_ptr<Texture> mDSTexture;
		UINT mRTCount;
	};
}

