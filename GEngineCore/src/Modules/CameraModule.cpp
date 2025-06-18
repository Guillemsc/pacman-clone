//
// Created by guillem on 6/15/25.
//

#include "CameraModule.h"

#include "InputModule.h"
#include "Cameras/Camera.h"
#include "Extensions/VectorExtensions.h"
#include "glm/gtc/quaternion.hpp"
#include "spdlog/spdlog.h"

namespace GEngineCore
{
	CameraModule::CameraModule()
	{
		_editorCamera = std::make_shared<Camera>();
		_editorCamera->SetPosition({0, 0, -500});
		_editorCamera->SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

		_currentRenderingCamera = _editorCamera;
	}

	void CameraModule::Tick(const float deltaTime)
	{
		TickEditorCamera(deltaTime);
	}

	std::weak_ptr<Camera> CameraModule::CreateCamera()
	{
		std::shared_ptr<Camera> camera = std::make_shared<Camera>();

		_cameras.push_back(camera);
		_currentCamera = camera;

		return camera;
	}

	void CameraModule::RemoveCamera(const std::weak_ptr<Camera> &cameraPtr)
	{
		const std::shared_ptr<Camera> camera = cameraPtr.lock();
		if (!camera) return;

		VectorExtensions::Remove(_cameras, camera);

		if (!_cameras.empty())
		{
			_currentCamera = *_cameras.end();
		}
	}

	std::weak_ptr<Camera> CameraModule::GetCurrentCamera()
	{
		return _currentCamera;
	}

	std::weak_ptr<Camera> CameraModule::GetCurrentRenderingCamera()
	{
		return _isUsingEditorCamera ? _editorCamera : _currentCamera;
	}

	bool CameraModule::GetIsUsingEditorCamera() const
	{
		return _isUsingEditorCamera;
	}

	void CameraModule::SetIsUsingEditorCamera(const bool value)
	{
		_isUsingEditorCamera = value;
	}

	void CameraModule::TickEditorCamera(float deltaTime)
	{
		if (!_isUsingEditorCamera)
		{
			return;
		}

		const float moveSpeed = InputModule::IsKeyDown(KEY_LEFT_SHIFT) ? 400.0f : 100.0f;
		constexpr float lookSensitivity = 0.1f;

		const glm::vec3 forward = _editorCamera->GetForwardDirection();
		const glm::vec3 right = _editorCamera->GetRightDirection();

		glm::vec3 position = _editorCamera->GetPosition();
		glm::quat rotation = _editorCamera->GetRotation();

		if (InputModule::IsKeyDown(KEY_W)) position -= forward * moveSpeed * deltaTime;
		if (InputModule::IsKeyDown(KEY_S)) position += forward * moveSpeed * deltaTime;
		if (InputModule::IsKeyDown(KEY_D)) position += right * moveSpeed * deltaTime;
		if (InputModule::IsKeyDown(KEY_A)) position -= right * moveSpeed * deltaTime;

		_editorCamera->SetPosition(position);

		glm::vec2 mousePos = InputModule::GetMousePosition();
		glm::vec2 delta = mousePos - _lastMousePos;
		_lastMousePos = mousePos;

		if (InputModule::IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			float yaw = delta.x * lookSensitivity * deltaTime;
			float pitch = delta.y * lookSensitivity * deltaTime;

			// Convert current rotation to euler, then apply pitch/yaw
			glm::vec3 euler = glm::eulerAngles(rotation);
			euler.x += pitch;
			euler.y += yaw;

			// Clamp pitch
			euler.x = glm::clamp(euler.x, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);

			rotation = glm::quat(euler);

			_editorCamera->SetRotation(rotation);
		}
	}
} // GEngineCore