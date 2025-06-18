//
// Created by guillem on 6/18/25.
//

#ifndef TEXTURERESOURCEINSPECTOREDITOR_H
#define TEXTURERESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "Resources/TextureResource.h"

namespace GEngineCore
{
	class TextureResourceInspectorEditor final : public ResourceInspectorEditor<TextureResource>
	{
	public:
		void DrawSpecific(const std::shared_ptr<TextureResource> &inspect) override;
	};
}

#endif //RESOURCETEXTUREINSPECTOREDITOR_H
