//
// Created by guillem on 7/12/25.
//

#ifndef TIMEMODULE_H
#define TIMEMODULE_H

namespace GEngine
{
	class TimeModule
	{
	public:
		[[nodiscard]] float GetDeltaTime() const;
		[[nodiscard]] int GetFps() const;
	};
}

#endif //TIMEMODULE_H
