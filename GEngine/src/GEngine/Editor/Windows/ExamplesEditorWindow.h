//
// Created by guillem on 7/12/25.
//

#ifndef EXAMPLESEDITORWINDOW_H
#define EXAMPLESEDITORWINDOW_H

#include "EditorWindow.h"

namespace GEngine
{
	class ExamplesEditorWindow final : public EditorWindow
	{
	public:
		explicit ExamplesEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;
	};
}

#endif //EXAMPLESEDITORWINDOW_H
