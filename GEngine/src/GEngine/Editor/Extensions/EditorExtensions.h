//
// Created by guillem on 6/25/25.
//

#ifndef EDITOREXTENSIONS_H
#define EDITOREXTENSIONS_H

#include <memory>

#include "GEngine/Raylib/RaylibWrapper.h"

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
		static void DrawRawTexture(const Texture& texture, const Rectangle& rectangle);
	};
}

#endif //EDITOREXTENSIONS_H
