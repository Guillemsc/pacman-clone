//
// Created by guillem on 6/17/25.
//

#ifndef MENUBAREDITOR_H
#define MENUBAREDITOR_H
#include <memory>

namespace GEngineCore
{
	class GEngineCoreApplication;

	class MenuBarEditor
	{
	public:
		explicit MenuBarEditor(const std::weak_ptr<GEngineCoreApplication>& app);

		void Draw();

	private:
		std::weak_ptr<GEngineCoreApplication> _app;
	};
}

#endif //MENUBAREDITOR_H
