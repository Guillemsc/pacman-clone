//
// Created by guillem on 6/17/25.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"

namespace GEngine
{
	class Camera;

	class CameraComponent final : public Component
	{
		DECLARE_COMPONENT(CameraComponent)

	public:
		explicit CameraComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnEnable() override;
		void OnTick() override;
		void OnDisable() override;

	private:
		std::weak_ptr<Camera> _camera;
	};
}

#endif //CAMERACOMPONENT_H
