#pragma once
#include "CResource.h"
#include "CTexture.h"

namespace yha
{
	using namespace math;
	using namespace graphics;

	class Animator;

	class CAnimation : public CResource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{
			}
		};

	public:
		CAnimation();
		~CAnimation();

	public:
		virtual HRESULT FnLoad(const std::wstring& path) { return S_FALSE; };

		void FnUpdate();
		void FnLateUpdate();
		void FnRender();

		void FnCreate(
			std::wstring name
			, std::shared_ptr<graphics::CTexture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void FnBinds();
		void FnReset();

		bool FnIsComplete() { return mbComplete; }

	private:
		std::shared_ptr<graphics::CTexture> mAtlas;
		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
