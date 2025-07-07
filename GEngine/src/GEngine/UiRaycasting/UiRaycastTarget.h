//
// Created by guillem on 7/7/25.
//

#ifndef UIRAYCASTTARGET_H
#define UIRAYCASTTARGET_H

#include "UiRaycastTargetState.h"

namespace GEngine
{
	class UiRaycastTarget
	{
		friend class UiModule;

	public:
		virtual ~UiRaycastTarget() = default;

		UiRaycastTargetState GetState() const { return _state; }

		virtual void OnMouseEnter() {};
		virtual void OnMouseExit() {};
		virtual void OnMouseUp() {};
		virtual void OnMouseDown() {};
		virtual void OnMouseClick() {};

	private:
		UiRaycastTargetState _state = UiRaycastTargetState::IDLE;
	};
}

#endif //UIRAYCASTTARGET_H
