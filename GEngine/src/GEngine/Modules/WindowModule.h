//
// Created by guillem on 6/7/25.
//

#ifndef WINDOWMODULE_H
#define WINDOWMODULE_H

namespace GEngine
{
	class WindowModule
	{
	public:
		void Init();
		bool CanRun();
		void Tick();
		void Dispose();
	};
}

#endif //WINDOWMODULE_H
