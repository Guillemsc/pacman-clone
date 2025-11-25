//
// Created by guillem on 11/25/25.
//

#include "Camera2d.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	Camera2d::Camera2d(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	void Camera2d::SetPosition(const glm::vec2 &position)
	{
		_position = position;
	}

	void Camera2d::SetRotation(const float rotation)
	{
		_rotation = rotation;
	}

	void Camera2d::SetHorizontalFov(const float zoom)
	{
		_horizontalFov = zoom;
	}

	Camera2D Camera2d::GetRawCamera() const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();
		const glm::vec2 halfWindowSize = windowSize * 0.5f;

		const glm::vec2 actualPosition = { -_position.x, _position.y };

		::Camera2D _rawCamera = {};
		_rawCamera.target = { -actualPosition.x, -actualPosition.y };
		_rawCamera.offset = { halfWindowSize.x, halfWindowSize.y };
		_rawCamera.rotation = 0;
		_rawCamera.zoom = MathExtensions::SafeDivide(windowSize.x, _horizontalFov);

		return _rawCamera;
	}
}
