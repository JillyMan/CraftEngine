#pragma once
#include <Craft\Math\Math.h>

namespace Craft
{
	enum class MoveDirection
	{
		Up,
		Down,
		Right,
		Left
	};

	class Camera
	{
	protected:
		v3 m_Position;
		v3 m_RotateAxis = { 0.0f, 0.0f, 1.0f };
		f32 m_Rotation = 0.0f;

		mat4 m_ViewMatrix;
		mat4 m_ProjectionMatrix;

	protected:
		Camera(mat4& projectionMatrix, v3& position = v3(), f32 cameraSpeed = 0.0f);
		virtual void RecalculateViewMatrix();

	public:
		inline mat4 GetViewProjectionMatrix() { return m_ProjectionMatrix * m_ViewMatrix; }

		inline mat4 GetViewMatrix() { return m_ViewMatrix; }
		inline mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }

		inline f32 GetRotation() { return m_Rotation; }
		inline virtual void SetRotation(f32 rotation, v3& axis) 
		{
			m_RotateAxis = axis;
			m_Rotation = rotation; 
			RecalculateViewMatrix();
		}

		inline const v3& GetPosition() { return m_Position; }
		inline void SetPosition(v3& position) 
		{ 
			m_Position = position; 
			RecalculateViewMatrix();
		}

		static Camera* CreatePerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position = v3(), f32 speed = 0.0f);
		static Camera* CreateOrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, v3& position = v3(), f32 speed = 0.1f);
	};
}