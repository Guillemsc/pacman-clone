//
// Created by guillem on 7/7/25.
//

#include "UiModule.h"

#include "EntitiesModule.h"
#include "InputModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiTransformComponent.h"

namespace GEngine
{
	void UiModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	void UiModule::Tick()
	{
		TickRaycastTargetsState();
	}

	void UiModule::Dispose()
	{
	}

	void UiModule::TickRaycastTargetsState()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<InputModule> input = app->Input().lock();
		if (!input) return;

		const glm::vec2 mousePosition = input->GetMousePosition();
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

		if (input->IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
		{
			if (const std::shared_ptr<UiRaycastTarget> currentRaycastTarget = _currentRaycastTargetPtr.lock())
			{
				currentRaycastTarget->_state = UiRaycastTargetState::MOUSE_DOWN;
				currentRaycastTarget->OnMouseDown();

				_canClick = true;
				_mouseDown = true;
			}
		}

		if (input->IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT))
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
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return std::shared_ptr<UiRaycastTarget>();

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();
		if (!entities) return std::shared_ptr<UiRaycastTarget>();

		std::shared_ptr<UiRaycastTarget> target;

		// We are going to be very naive and not optimize for now
		entities->ForEachEntityInHierarchy([&target, mousePosition](const std::shared_ptr<Entity> &entity)
		{
			const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
			if (!transform) return;

			const std::shared_ptr<UiRaycastTarget> raycastTarget = entity->GetComponent<UiRaycastTarget>().lock();
			if (!raycastTarget) return;

			const bool containsTarget = transform->IsContainedInScreenRect(mousePosition);
			if (!containsTarget) return;

			target = raycastTarget;
		});

		return target;
	}
}
