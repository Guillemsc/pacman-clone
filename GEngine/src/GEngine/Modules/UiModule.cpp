//
// Created by guillem on 7/7/25.
//

#include "UiModule.h"

#include "EntitiesModule.h"
#include "InputModule.h"
#include "WindowModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Extensions/MathExtensions.h"

namespace GEngine
{
	void UiModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;
	}

	void UiModule::Tick()
	{
		TickRaycastTargetsState();
	}

	void UiModule::Dispose()
	{
	}

	void UiModule::SetReferenceScreenSize(const glm::vec2 &size)
	{
		_referenceScreenSize = size;
		RecalculateUiScaleAndRefreshUiTransforms();
	}

	float UiModule::GetUiScale() const
	{
		return _uiScale;
	}

	void UiModule::TickRaycastTargetsState()
	{
		const glm::vec2 mousePosition = _modules->input->GetMousePosition();
		const std::shared_ptr<UiRaycastTarget> targetPtr = RaycastAtScreenPosition(mousePosition);

		if (_currentRaycastTargetPtr.lock() != targetPtr)
		{
			if (const std::shared_ptr<UiRaycastTarget> raycastTarget = _currentRaycastTargetPtr.lock())
			{
				raycastTarget->_state = UiRaycastTargetState::IDLE;

				if (_mouseDown)
				{
					raycastTarget->OnMouseUp();
				}

				raycastTarget->OnMouseExit();
			}

			_mouseDown = false;
			_canClick = false;

			if (targetPtr != nullptr)
			{
				targetPtr->_state = UiRaycastTargetState::MOUSE_INSIDE;
				targetPtr->OnMouseEnter();
			}
		}

		_currentRaycastTargetPtr = targetPtr;

		if (_modules->input->IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
		{
			if (const std::shared_ptr<UiRaycastTarget> currentRaycastTarget = _currentRaycastTargetPtr.lock())
			{
				currentRaycastTarget->_state = UiRaycastTargetState::MOUSE_DOWN;
				currentRaycastTarget->OnMouseDown();

				_canClick = true;
				_mouseDown = true;
			}
		}

		if (_modules->input->IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT))
		{
			if (_canClick)
			{
				if (const std::shared_ptr<UiRaycastTarget> currentRaycastTarget = _currentRaycastTargetPtr.lock())
				{
					targetPtr->_state = UiRaycastTargetState::MOUSE_INSIDE;

					if (_mouseDown)
					{
						currentRaycastTarget->OnMouseUp();
					}

					currentRaycastTarget->OnMouseClick();
				}
			}
		}
	}


	std::shared_ptr<UiRaycastTarget> UiModule::RaycastAtScreenPosition(const glm::vec2& mousePosition) const
	{
		std::shared_ptr<UiRaycastTarget> target;

		// We are going to be very naive and not optimize for now
		_modules->entities->ForEachEntityInHierarchy([&target, mousePosition](const std::shared_ptr<Entity> &entity)
		{
			const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
			if (!transform) return;

			const std::shared_ptr<UiRaycastTarget> raycastTarget = entity->GetComponent<UiRaycastTarget>().lock();
			if (!raycastTarget) return;

			const bool containsTarget = transform->IsContainedInWorldRect(mousePosition);
			if (!containsTarget) return;

			target = raycastTarget;
		});

		return target;
	}

	void UiModule::RecalculateUiScaleAndRefreshUiTransforms()
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();

		_uiScale = MathExtensions::GetNormalizedValue(windowSize.x, _referenceScreenSize.x);

		_modules->entities->RefreshUiTransforms();
	}

	glm::vec2 UiModule::GetReferenceScreenSize() const
	{
		return _referenceScreenSize;
	}
}
