#pragma once
#include <Craft\Math\Math.h>

namespace Craft
{
	class Camera
	{
	protected:
		v3 m_Position;
		f32 m_Rotation = 0.0f;

		mat4 m_ProjectionMatrix;
		mat4 m_ViewProjectionMatrix;

	protected:
		Camera(mat4& projectionMatrix, v3& position);
		virtual void RecalculateMatrix() = 0;

	public:
		inline mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		inline f32 GetRotation() { return m_Rotation; }
		inline void SetRotation(f32 rotation) 
		{ 
			m_Rotation = rotation; 
			RecalculateMatrix(); 
		}

		inline const v3& GetPosition() { return m_Position; }
		inline void SetPosition(v3& position) 
		{ 
			m_Position = position; 
			RecalculateMatrix(); 
		}

		static Camera* CreatePerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position = v3());
		static Camera* CreateOrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, v3& position = v3());
	};
}