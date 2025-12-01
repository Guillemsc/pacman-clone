//
// Created by guillem on 12/1/25.
//

#ifndef SPRITERESOURCEINSPECTOREDITOR_H
#define SPRITERESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "GEngine/Resources/SpriteResource.h"

namespace GEngine
{
	class SpriteResource;

	class SpriteResourceInspectorEditor final : public ResourceInspectorEditor<SpriteResource>
	{
	public:
		explicit SpriteResourceInspectorEditor(GEngineCoreModules* modules);

		void DrawSpecific(const std::shared_ptr<SpriteResource> &inspect) override;
	};
}

#endif //SPRITERESOURCEINSPECTOREDITOR_H
