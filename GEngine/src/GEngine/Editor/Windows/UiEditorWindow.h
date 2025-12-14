//
// Created by guillem on 7/14/25.
//

#ifndef UIEDITORWINDOW_H
#define UIEDITORWINDOW_H

#include "EditorWindow.h"

namespace GEngine
{
	class UiEditorWindow final : public EditorWindow
	{
	public:
		explicit UiEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;
	};
}

#endif //UIEDITORWINDOW_H
