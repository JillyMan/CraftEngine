#pragma once

#include "Camera.h"

namespace Craft
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position);

	protected:
		virtual void PerspectiveCamera::RecalculateMatrix() override;
	};

}