//
// Created by guillem on 7/14/25.
//

#ifndef UIEDITORWINDOW_H
#define UIEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngine
{
	class UiEditorWindow : public EditorWindow
	{
	public:
		explicit UiEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void DrawWindowContent() override;
	};
}

#endif //UIEDITORWINDOW_H
