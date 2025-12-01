//
// Created by guillem on 6/9/25.
//

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <memory>
#include <string>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;

	class EditorWindow
	{
	public:
		explicit EditorWindow(GEngineCoreModules* modules, const std::string& windowTitle);

		virtual void Draw();

		std::string GetTitle() const;

	protected:
		virtual void DrawWindowContent() = 0;

	public:
		bool Visible = true;

	protected:
		GEngineCoreModules* const _modules;

	private:
		std::string _title;
	};
}

#endif //EDITORWINDOW_H
