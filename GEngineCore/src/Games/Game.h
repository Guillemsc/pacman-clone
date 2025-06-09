//
// Created by guillem on 6/7/25.
//

#ifndef GAME_H
#define GAME_H

#include <memory>

namespace GEngineCore
{
	class GEngineCoreApplication;

	class Game
	{
	public:
		virtual ~Game() = default;
		void Setup(const std::weak_ptr<GEngineCoreApplication> &app) { _app = app; }

		virtual void Init() = 0;
		virtual void Tick() = 0;
		virtual void Dispose() = 0;

	protected:
		std::weak_ptr<GEngineCoreApplication> _app;
	};
}

#endif //GAME_H
