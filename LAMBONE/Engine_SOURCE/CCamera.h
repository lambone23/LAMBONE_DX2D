#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace yha
{
	class CCamera : public CComponent
	{
	public:
		CCamera();
		~CCamera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}