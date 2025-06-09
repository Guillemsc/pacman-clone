//
// Created by guillem on 6/9/25.
//

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H
#include <memory>

namespace GEngineCore
{
	class GEngineCoreApplication;

	class EditorWindow
	{
	public:
		explicit EditorWindow(const std::weak_ptr<GEngineCoreApplication>& app);

		virtual void Draw() = 0;

	public:
		bool visible = true;

	protected:
		std::weak_ptr<GEngineCoreApplication> _app;
	};
}

#endif //EDITORWINDOW_H
