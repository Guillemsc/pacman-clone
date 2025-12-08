//
// Created by guillem on 6/17/25.
//

#include "CameraComponent.h"

#include "TransformComponent.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/CameraModule.h"

namespace GEngine
{
	CameraComponent::CameraComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity) : Component(modules, entity)
	{
	}

	void CameraComponent::OnEnable()
	{
		_camera = modules->camera->CreateCamera();
	}

	void CameraComponent::OnTick()
	{
		const std::shared_ptr<Camera> camera = _camera.lock();
		if (!camera) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (!entity) return;

		const glm::vec3 position = transform->GetPosition();
		const glm::quat rotation = transform->GetRotation();

		camera->SetPosition(position);
		camera->SetRotation(rotation);
	}

	void CameraComponent::OnDisable()
	{
		modules->camera->RemoveCamera(_camera);
		_camera.reset();
	}
} // GEngineCore