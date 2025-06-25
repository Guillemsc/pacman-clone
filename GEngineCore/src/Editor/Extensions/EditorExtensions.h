//
// Created by guillem on 6/25/25.
//

#ifndef EDITOREXTENSIONS_H
#define EDITOREXTENSIONS_H

#include <memory>

namespace GEngineCore
{
	class EditorModule;
	class Resource;

	class EditorExtensions
	{
	public:
		static void DrawResource(
			EditorModule* editor,
			const char* resourceName,
			const std::weak_ptr<Resource> &resourcePtr
			);
	};
}

#endif //EDITOREXTENSIONS_H
