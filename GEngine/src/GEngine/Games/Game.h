//
// Created by guillem on 6/7/25.
//

#ifndef GAME_H
#define GAME_H

#include <memory>

namespace GEngine
{
	class GEngineCoreModules;
	class GEngineCoreApplication;

	class Game
	{
	public:
		explicit Game(const std::string& name) : _name(name) {}
		virtual ~Game() = default;

		void Setup(GEngineCoreModules* modules) { _modules = modules; }

		std::string GetName() { return _name; }

		virtual void Init() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Dispose() = 0;

	protected:
		std::string _name;

		GEngineCoreModules* _modules = nullptr;
	};
}

#endif //GAME_H
