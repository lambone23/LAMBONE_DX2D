#include "CAnimation.h"
#include "CTime.h"
#include "CAnimator.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"

namespace yha
{
	CAnimation::CAnimation()
		: CResource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	CAnimation::~CAnimation()
	{
	}

	void CAnimation::FnUpdate()
	{
	}//END-void CAnimation::FnUpdate

	void CAnimation::FnLateUpdate()
	{
		if (mbComplete)
			return;

		mTime += CTime::FnDeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}//END-void CAnimation::FnLateUpdate

	void CAnimation::FnRender()
	{
	}//END-void CAnimation::FnRender

	void CAnimation::FnCreate(
		std::wstring name
		, std::shared_ptr<graphics::CTexture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		FnSetKey(name);
		mAtlas = atlas;


		float width = (float)atlas->FnGetWidth();
		float height = (float)atlas->FnGetHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}
	}//END-void CAnimation::FnCreate

	void CAnimation::FnBinds()
	{
		// texture bind
		mAtlas->FnBindShaderResource(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;

		CConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->FnSetData(&data);

		cb->FnBind(eShaderStage::VS);
		cb->FnBind(eShaderStage::PS);
	}//END-void CAnimation::FnBinds

	void CAnimation::FnReset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}//END-void CAnimation::FnReset
}