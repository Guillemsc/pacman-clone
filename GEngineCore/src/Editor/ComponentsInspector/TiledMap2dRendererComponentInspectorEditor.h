//
// Created by guillem on 6/25/25.
//

#ifndef TILEDMAP2DRENDERERCOMPONENTINSPECTOREDITOR_H
#define TILEDMAP2DRENDERERCOMPONENTINSPECTOREDITOR_H

#include "ComponentInspectorEditor.h"
#include "Components/TiledMap2dRendererComponent.h"

namespace GEngineCore
{
	class TiledMap2dRendererComponentInspectorEditor final : public ComponentInspectorEditor<TiledMap2dRendererComponent>
	{
	public:
		explicit TiledMap2dRendererComponentInspectorEditor(const std::weak_ptr<GEngineCoreApplication>& app);

		void DrawSpecific(const std::shared_ptr<TiledMap2dRendererComponent>& inspect) override;
	};
}

#endif //TILEDMAP2DRENDERERCOMPONENTINSPECTOREDITOR_H
