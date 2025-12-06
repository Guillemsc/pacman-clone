//
// Created by guillem on 11/25/25.
//

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "GEngine/Raylib/RaylibWrapper.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class GEngineCoreModules;

	class Camera2d
	{
		friend class CameraModule;

	public:
		explicit Camera2d(GEngineCoreModules* modules);

		void SetPosition(const glm::vec2& position);
		void SetRotation(float rotation);
		void SetHorizontalFov(float zoom);

		[[nodiscard]] ::Camera2D GetRawCamera() const;

	private:
		GEngineCoreModules* const _modules = nullptr;

		glm::vec2 _position = glm::vec2(0, 0);
		float _rotation = 0;
		float _horizontalFov = 1;
	};
}

#endif //CAMERA2D_H
