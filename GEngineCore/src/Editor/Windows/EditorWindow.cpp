//
// Created by guillem on 6/9/25.
//

#include "EditorWindow.h"

namespace GEngineCore
{
	EditorWindow::EditorWindow(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}
} // GEngineCore