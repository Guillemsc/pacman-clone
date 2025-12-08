//
// Created by guillem on 6/17/25.
//

#ifndef MENUBAREDITOR_H
#define MENUBAREDITOR_H

#include <memory>

namespace GEngine
{
	class GEngineCoreModules;
	class GEngineCoreApplication;

	class MenuBarEditor
	{
	public:
		explicit MenuBarEditor(GEngineCoreModules* modules);

		void Draw() const;

	private:
		void DrawWindows() const;

	private:
		GEngineCoreModules* const _modules = nullptr;
	};
}

#endif //MENUBAREDITOR_H
