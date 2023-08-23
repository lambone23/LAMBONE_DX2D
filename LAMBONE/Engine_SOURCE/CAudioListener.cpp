#include "CAudioListener.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CFmod.h"

namespace yha
{
	CAudioListener::CAudioListener()
		: CComponent(eComponentType::AudioListener)
	{
	}

	CAudioListener::~CAudioListener()
	{
	}

	void CAudioListener::FnInitialize()
	{
	}

	void CAudioListener::FnUpdate()
	{
	}

	void CAudioListener::FnLateUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		Vector3 foward = tr->FnFoward();
		Vector3 up = tr->FnUp();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		CFmod::FnSet3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void CAudioListener::FnRender()
	{
	}
}