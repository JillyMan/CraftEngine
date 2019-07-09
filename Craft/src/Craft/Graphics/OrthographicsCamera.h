#pragma once

#include "Craft/Math/Math.h"

namespace Craft
{
	class OrthographicsCamera
	{
	private:
		mat4 m_ProjectionMatrix;
		mat4 m_ViewMatrix;
		mat4 m_ViewProjectionMatrix;

		v3 m_Position;
		f32 m_Rotation;

	public:
		OrthographicsCamera(f32 left, f32 right, f32 bottom, f32 top);

		inline void SetRotation(f32 rotation) { m_Rotation = rotation; RecalculateMatrix(); }
		inline f32 GetRotation() { return m_Rotation; }

		inline void SetPosition(v3 position) { m_Position = position; RecalculateMatrix(); }
		inline const v3& GetPosition() { return m_Position; }

		inline mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void RecalculateMatrix();
	};
}