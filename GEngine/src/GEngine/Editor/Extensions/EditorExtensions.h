//
// Created by guillem on 6/25/25.
//

#ifndef EDITOREXTENSIONS_H
#define EDITOREXTENSIONS_H

#include <memory>

#include "raylib.h"

namespace GEngine
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
		static void DrawRawTexture(const Texture& texture);
	};
}

#endif //EDITOREXTENSIONS_H
