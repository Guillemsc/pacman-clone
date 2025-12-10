//
// Created by guillem on 7/27/25.
//

#ifndef TWEENSDEVELOPMENTEXAMPLE_H
#define TWEENSDEVELOPMENTEXAMPLE_H

#include "GEngine/Games/Game.h"
#include "GEngine/Tweens/Tween.h"

namespace GEngine
{
	class DevelopmentTweensExample final : public Game
	{
	public:
		DevelopmentTweensExample();

		void Init() override;
		void Tick(float deltaTime) override;
		void Dispose() override;

	private:
		std::shared_ptr<Tween> _tween;
		float _value = 0.0f;
	};
}

#endif //TWEENSDEVELOPMENTEXAMPLE_H
