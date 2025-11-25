//
// Created by guillem on 6/18/25.
//

#ifndef TEXTURERESOURCEINSPECTOREDITOR_H
#define TEXTURERESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "GEngine/Resources/TextureResource.h"

namespace GEngine
{
	class GEngineCoreApplication;

	class TextureResourceInspectorEditor final : public ResourceInspectorEditor<TextureResource>
	{
	public:
		explicit TextureResourceInspectorEditor(GEngineCoreModules* modules);

		void DrawSpecific(const std::shared_ptr<TextureResource> &inspect) override;
	};
}

#endif //RESOURCETEXTUREINSPECTOREDITOR_H
