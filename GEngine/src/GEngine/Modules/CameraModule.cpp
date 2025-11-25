//
// Created by guillem on 6/15/25.
//

#include "CameraModule.h"

#include "InputModule.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Cameras/Camera2d.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "glm/gtc/quaternion.hpp"
#include "spdlog/spdlog.h"

namespace GEngine
{
	CameraModule::CameraModule()
	{

	}

	void CameraModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		_editorCamera = std::make_shared<Camera>(_modules);
		_editorCamera->SetPosition({0, 0, -500});
		_editorCamera->SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

		_editorCamera2d = std::make_shared<Camera2d>(_modules);
		_editorCamera2d->SetPosition({0, 0});
	}

	void CameraModule::Tick(const float deltaTime)
	{
		TickEditorCamera(deltaTime);
	}

	bool CameraModule::IsUsing2dMode() const
	{
		return _isUsing2dMode;
	}

	std::weak_ptr<Camera> CameraModule::CreateCamera()
	{
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(_modules);

		_cameras.push_back(camera);
		_currentCamera = camera;

		return camera;
	}

	void CameraModule::RemoveCamera(const std::weak_ptr<Camera>& removing)
	{
		const std::shared_ptr<Camera> camera = removing.lock();
		if (!camera) return;

		VectorExtensions::Remove(_cameras, camera);

		if (!_cameras.empty())
		{
			_currentCamera = *_cameras.end();
		}
	}

	std::weak_ptr<Camera2d> CameraModule::CreateCamera2d()
	{
		std::shared_ptr<Camera2d> camera = std::make_shared<Camera2d>(_modules);

		_cameras2d.push_back(camera);
		_currentCamera2d = camera;

		return camera;
	}

	void CameraModule::RemoveCamera2d(const std::weak_ptr<Camera2d> &removing)
	{
		const std::shared_ptr<Camera2d> camera = removing.lock();
		if (!camera) return;

		VectorExtensions::Remove(_cameras2d, camera);

		if (!_cameras2d.empty())
		{
			_currentCamera2d = *_cameras2d.end();
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

	std::weak_ptr<Camera2d> CameraModule::GetCurrentCamera2d()
	{
		return _currentCamera2d;
	}

	std::weak_ptr<Camera2d> CameraModule::GetCurrentRenderingCamera2d()
	{
		return _isUsingEditorCamera ? _editorCamera2d : _currentCamera2d;
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

		glm::vec2 mousePos = _modules->input->GetMousePosition();
		glm::vec2 delta = mousePos - _lastMousePos;
		_lastMousePos = mousePos;

		if (InputModule::IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			float yaw = delta.x * lookSensitivity * deltaTime;
			float pitch = -delta.y * lookSensitivity * deltaTime;

			glm::quat yawQuat = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
			rotation = yawQuat * rotation;

			glm::vec3 localRight = rotation * glm::vec3(1, 0, 0);
			glm::quat pitchQuat = glm::angleAxis(pitch, localRight);
			rotation = pitchQuat * rotation;

			_editorCamera->SetRotation(rotation);
		}
	}
} // GEngineCore