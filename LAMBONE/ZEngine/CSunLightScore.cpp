#include "CSunLightScore.h"
#include "CFontWrapper.h"

namespace yha
{
	CSunLightScore::CSunLightScore()
	{
	}
	CSunLightScore::~CSunLightScore()
	{
		CFontWrapper::FnRelease();
	}
	void CSunLightScore::FnInitialize()
	{
		CFontWrapper::FnInitialize();
		CGameObject::FnInitialize();
	}
	void CSunLightScore::FnUpdate()
	{
		CGameObject::FnUpdate();
	}
	void CSunLightScore::FnLateUpdate()
	{
	}
	void CSunLightScore::FnRender()
	{
		CGameObject::FnRender();
	}
	void CSunLightScore::FnRender_Font()
	{
		//CFontWrapper::FnDrawFont(_szFloat, 825, 60, 25, FONT_RGBA(255, 0, 255, 255));
		//CFontWrapper::FnDrawFont(L"Sample_Application", 100, 100, 25, FONT_RGBA(255, 0, 255, 255));
	}
}