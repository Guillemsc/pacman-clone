//
// Created by guillem on 11/24/25.
//

#ifndef TWEENSMODULE_H
#define TWEENSMODULE_H

#include <memory>
#include <vector>

#include "tokoro.h"

namespace GEngine
{
	class GEngineCoreModules;
	class CancellationToken;
	class Tween;

	class TweensModule
	{
	public:
		void Init(GEngineCoreModules* modules);
		void Tick();
		void Dispose();

		bool Play(const std::shared_ptr<Tween>& tween);
		tokoro::Async<void> PlayAsync(const std::shared_ptr<Tween>& tween, CancellationToken cancellationToken);
		tokoro::Async<void> PlayAsync(const std::shared_ptr<Tween>& tween);

	private:
		GEngineCoreModules* _modules = nullptr;

		std::vector<std::shared_ptr<Tween>> _tweens;
	};
}

#endif //TWEENSMODULE_H
