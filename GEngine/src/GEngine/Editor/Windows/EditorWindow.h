//
// Created by guillem on 6/9/25.
//

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H
#include <memory>

namespace GEngine
{
	class GEngineCoreApplication;

	class EditorWindow
	{
	public:
		explicit EditorWindow(const std::weak_ptr<GEngineCoreApplication>& app, const std::string& windowTitle);

		virtual void Draw();

		std::string GetTitle() const;

	protected:
		virtual void DrawWindowContent() = 0;

	public:
		bool Visible = true;

	private:
		std::string _title;

	protected:
		std::weak_ptr<GEngineCoreApplication> _app;
	};
}

#endif //EDITORWINDOW_H
