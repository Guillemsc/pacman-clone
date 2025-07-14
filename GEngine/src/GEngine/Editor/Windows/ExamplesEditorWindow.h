//
// Created by guillem on 7/12/25.
//

#ifndef EXAMPLESEDITORWINDOW_H
#define EXAMPLESEDITORWINDOW_H

#include "EditorWindow.h"

namespace GEngine
{
	class ExamplesEditorWindow : public EditorWindow
	{
	public:
		explicit ExamplesEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void DrawWindowContent() override;
	};
}

#endif //EXAMPLESEDITORWINDOW_H
