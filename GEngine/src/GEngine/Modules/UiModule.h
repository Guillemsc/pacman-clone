//
// Created by guillem on 7/7/25.
//

#ifndef UIMODULE_H
#define UIMODULE_H

#include <memory>

#include "glm/vec2.hpp"

namespace GEngine
{
	class GEngineCoreModules;
	class UiRaycastTarget;
	class Entity;

	class UiModule
	{
	public:
		void Init(GEngineCoreModules* modules);

		void Tick();
		void Dispose();

		void SetReferenceScreenSize(const glm::vec2& size);
		void RecalculateUiScaleAndRefreshUiTransforms();

		glm::vec2 GetReferenceScreenSize() const;
		float GetUiScale() const;

	private:
		void TickRaycastTargetsState();
		std::shared_ptr<UiRaycastTarget> RaycastAtScreenPosition(const glm::vec2& mousePosition) const;

	private:
		GEngineCoreModules* _modules = nullptr;

		glm::vec2 _referenceScreenSize = glm::vec2(1280, 720);
		float _uiScale = 1;

		std::weak_ptr<UiRaycastTarget> _currentRaycastTargetPtr;
		bool _mouseDown = false;
		bool _canClick = false;
	};
}

#endif //UIMODULE_H
