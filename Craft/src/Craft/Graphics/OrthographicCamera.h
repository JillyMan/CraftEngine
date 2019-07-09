#pragma once

#include "Camera.h"

namespace Craft
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, v3& position);

	protected:
		virtual void RecalculateMatrix() override;
	};
}