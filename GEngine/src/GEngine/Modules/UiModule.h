//
// Created by guillem on 7/7/25.
//

#ifndef UIMODULE_H
#define UIMODULE_H

#include <memory>

#include "glm/vec2.hpp"

namespace GEngine
{
	class UiRaycastTarget;
	class Entity;
	class GEngineCoreApplication;

	class UiModule
	{
	public:
		void Init(const std::weak_ptr<GEngineCoreApplication>& app);

		void Tick();
		void Dispose();

	private:
		void TickRaycastTargetsState();
		std::shared_ptr<UiRaycastTarget> RaycastAtScreenPosition(const glm::vec2& mousePosition) const;

	private:
		std::weak_ptr<GEngineCoreApplication> _app;

		std::weak_ptr<UiRaycastTarget> _currentRaycastTargetPtr;
		bool _mouseDown = false;
		bool _canClick = false;
	};
}

#endif //UIMODULE_H
