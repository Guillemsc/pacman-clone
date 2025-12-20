//
// Created by guillem on 12/19/25.
//

#ifndef WAITTWEEN_H
#define WAITTWEEN_H

#include "Tween.h"

namespace GEngine
{
	class WaitTween final : public Tween
	{
	public:
		explicit WaitTween(float duration);

	protected:
		void OnStart() override;
		void OnTick(float deltaTime) override;

	private:
		float _duration = 0.0f;
		float _currentTime = 0.0f;
	};
}

#endif //WAITTWEEN_H
