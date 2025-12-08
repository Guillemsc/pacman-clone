//
// Created by guillem on 6/8/25.
//

#ifndef SYSTEMSMODULE_H
#define SYSTEMSMODULE_H

#include <memory>
#include <vector>

namespace GEngine
{
	class Tickable;

	class TickablesModule
	{
	public:
		TickablesModule();

		void Tick() const;
		void Dispose();

		void AddTickable(const std::shared_ptr<Tickable>& tickable);
		void RemoveTickable(const std::shared_ptr<Tickable>& tickable);

		void RemoveAllTickablesNow();

	private:
		void TickTickables() const;

	private:
		std::vector<std::shared_ptr<Tickable>> _tickables;
	};
}

#endif //SYSTEMSMODULE_H
