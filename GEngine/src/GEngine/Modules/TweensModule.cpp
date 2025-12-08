//
// Created by guillem on 11/24/25.
//

#include "TweensModule.h"

#include "TimeModule.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Tweens/Tween.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	void TweensModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;
	}

	void TweensModule::Tick()
	{
		const float deltaTime = _modules->time->GetDeltaTime();

		for (int i = _tweens.size() - 1; i >= 0; --i)
		{
			const std::shared_ptr<Tween> tween = _tweens[i];

			tween->Tick(deltaTime);

			if (!tween->IsPlaying())
			{
				VectorExtensions::RemoveAt(_tweens, i);
			}
		}
	}

	void TweensModule::Dispose()
	{
		_tweens.clear();
	}

	bool TweensModule::Play(const std::shared_ptr<Tween> &tween)
	{
		if (!tween) return false;

		if (tween->IsPlaying()) return false;

		tween->Start();

		_tweens.push_back(tween);

		return true;
	}

	tokoro::Async<void> TweensModule::PlayAsync(
		const std::shared_ptr<Tween>& tween,
		const CancellationToken cancellationToken
		)
	{
		const bool couldPlay = Play(tween);

		if (!couldPlay) co_return;

		while (tween->IsPlaying())
		{
			if (cancellationToken.IsCancelled())
			{
				tween->Kill();
				co_return;
			}

			co_await tokoro::Wait();
		}
	}

	tokoro::Async<void> TweensModule::PlayAsync(const std::shared_ptr<Tween> &tween)
	{
		return PlayAsync(tween, CancellationToken::None());
	}
} // GEngine