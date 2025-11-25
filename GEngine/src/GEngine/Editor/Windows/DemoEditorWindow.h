//
// Created by guillem on 7/14/25.
//

#ifndef DEMOEDITORWINDOW_H
#define DEMOEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngine
{
	class DemoEditorWindow : public EditorWindow
	{
	public:
		explicit DemoEditorWindow(GEngineCoreModules* modules);

		void Draw() override;
		void DrawWindowContent() override;
	};
}

#endif //DEMOEDITORWINDOW_H
