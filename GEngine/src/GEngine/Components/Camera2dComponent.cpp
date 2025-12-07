//
// Created by guillem on 11/25/25.
//

#include "Camera2dComponent.h"

#include "TransformComponent.h"
#include "GEngine/Cameras/Camera2d.h"
#include "GEngine/Modules/CameraModule.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	Camera2dComponent::Camera2dComponent(GEngineCoreModules *modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
		_horizontalFovProperty = _properties.Register("Horizontal Fov", 150.0f);
	}

	void Camera2dComponent::OnEnable()
	{
		_camera = modules->camera->CreateCamera2d();
	}

	void Camera2dComponent::OnTick()
	{
		const std::shared_ptr<Camera2d> camera = _camera.lock();
		if (!camera) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (!entity) return;

		const glm::vec2 position = transform->GetPositionXY();
		const glm::vec3 rotation = transform->GetRotationEuler();
		const float zoom = _horizontalFovProperty->GetValue();

		camera->SetPosition(position);
		camera->SetRotation(rotation.z);
		camera->SetHorizontalFov(zoom);
	}

	void Camera2dComponent::OnDisable()
	{
		modules->camera->RemoveCamera2d(_camera);
		_camera.reset();
	}

	void Camera2dComponent::SetHorizontalFov(const float zoom) const
	{
		_horizontalFovProperty->SetValue(zoom);
	}

	void Camera2dComponent::EncapsulateBounds(const glm::vec2& bounds) const
	{
		const glm::vec2 windowSize = modules->window->GetWindowSize();
		const float windowHorizontalAspectRatio = windowSize.x / windowSize.y;
		const float boundsHorizontalAspectRatio = bounds.x / bounds.y;

		float horizontalFov;

		if (windowHorizontalAspectRatio > boundsHorizontalAspectRatio)
		{
			horizontalFov = bounds.y * windowHorizontalAspectRatio;
		}
		else
		{
			horizontalFov = bounds.x;
		}

		_horizontalFovProperty->SetValue(horizontalFov);
	}
}
