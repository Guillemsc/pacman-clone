//
// Created by guillem on 7/28/25.
//

#ifndef CALLBACKTWEEN_H
#define CALLBACKTWEEN_H

#include <functional>

#include "Tween.h"

namespace GEngine
{
	class CallbackTween : public Tween
	{
	public:
		explicit CallbackTween(const std::function<void()>& callback);

	protected:
		void OnStart() override;

	private:
		std::function<void()> _callback;
	};
}

#endif //CALLBACKTWEEN_H
