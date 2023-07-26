#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace yha
{
	using namespace graphics;
	class CLight : public CComponent
	{
	public:
		CLight();
		~CLight();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		LightAttribute FnGetAttribute() { return mAttribute; }
		void FnSetType(eLightType rype) { mAttribute.type = rype; }
		void FnSetRadius(float radius) { mAttribute.radius = radius; }
		void FnSetAngle(float angle) { mAttribute.angle = angle; }
		void FnSetColor(Vector4 color) { mAttribute.color = color; }
		Vector4 FnGetColor() { return mAttribute.color; }
		eLightType FnGetType() { return mAttribute.type; }
		float FnGetRadius() { return mAttribute.radius; }
		float FnGetAngle() { return mAttribute.angle; }

	private:
		LightAttribute mAttribute;
	};
}
