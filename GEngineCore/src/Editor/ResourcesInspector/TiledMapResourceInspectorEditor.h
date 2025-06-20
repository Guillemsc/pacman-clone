//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAPRESOURCEINSPECTOREDITOR_H
#define TILEDMAPRESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "Resources/TiledMapResource.h"

namespace GEngineCore
{
	class TiledMapResourceInspectorEditor final : public ResourceInspectorEditor<TiledMapResource>
	{
	public:
		void DrawSpecific(const std::shared_ptr<TiledMapResource> &inspect) override;
	};
}

#endif //TILEDMAPRESOURCEINSPECTOREDITOR_H
