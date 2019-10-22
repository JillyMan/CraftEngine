#include "crpch.h"

#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Cameras/OrthographicCamera.h>
#include <Craft/Graphics/Cameras/PerspectiveCamera.h>

namespace Craft
{
	Camera::Camera(mat4& projectionMatrix, v3& position, f32 cameraSpeed) :
		m_Position(position),
		m_CameraSpeed(cameraSpeed),
		m_ProjectionMatrix(projectionMatrix),
		m_Scale(v3(1.0f, 1.0f, 1.0f))
	{
	}

	void Camera::Move(MoveDirection dir, f32 dt)
	{
		v3& P = m_Position;
		if (dir == MoveDirection::Up) {
			P.z += m_CameraSpeed * dt;
		}
		if (dir == MoveDirection::Down) {
			P.z -= m_CameraSpeed * dt;
		}
		if (dir == MoveDirection::Right) {
			P.x -= m_CameraSpeed * dt;
		}
		if (dir == MoveDirection::Left) {
			P.x += m_CameraSpeed * dt;
		}
		RecalculateViewMatrix();
	}

	Camera* Camera::CreatePerspectiveCamera(f32 fov, f32 aspectRatio, f32 _near, f32 _far, v3& position, f32 speed)
	{
		return new PerspectiveCamera(fov, aspectRatio, _near, _far, position, speed);
	}

	Camera* Camera::CreateOrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 _near, f32 _far, v3& position, f32 speed)
	{
		return new OrthographicCamera(left, right, bottom, top, _near, _far, position, speed);
	}

	void Camera::RecalculateViewMatrix()
	{
		m_ViewMatrix = mat4::Translate(m_Position) * mat4::Scale(m_Scale) * mat4::Rotate(m_Rotation, m_RotateAxis);
	}
}