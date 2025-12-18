//
// Created by guillem on 6/25/25.
//

#include "TiledMap2dRendererComponentInspectorEditor.h"

#include "imgui.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Editor/Extensions/EditorExtensions.h"
#include "GEngine/Resources/TiledMapResource.h"

namespace GEngine
{
	TiledMap2dRendererComponentInspectorEditor::TiledMap2dRendererComponentInspectorEditor(GEngineCoreModules* modules)
		: ComponentInspectorEditor(modules)
	{
	}

	void TiledMap2dRendererComponentInspectorEditor::DrawSpecific(const std::shared_ptr<TiledMap2dRendererComponent> &inspect)
	{
		const std::shared_ptr<TiledMapResource> tiledMapResource = inspect->GetTiledMap().lock();

		EditorExtensions::DrawResource(_modules->editor, "Tiled Map", tiledMapResource);

		if (tiledMapResource)
		{
			const std::shared_ptr<tmx::Map> rawMap = tiledMapResource->GetRawMap().lock();

			if (rawMap)
			{
				const std::vector<tmx::Layer::Ptr>& layers = rawMap->getLayers();

				ImGui::Spacing();
				ImGui::CollapsingHeader("Tile Layers", ImGuiTreeNodeFlags_Leaf);

				std::int32_t layerIndex = 0;
				for (const auto& layer : layers)
				{
					ImGui::PushID(layerIndex);

					if (ImGui::CollapsingHeader(layer->getName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
					{
						bool visible = inspect->GetIsTileLayerVisible(layerIndex);
						if (ImGui::Checkbox("Visible", &visible))
						{
							inspect->SetTileLayerVisible(layerIndex, visible);
						}

						std::int32_t renderLayerOffset = inspect->GetTileLayerRenderLayerOffset(layerIndex);
						if (ImGui::DragInt("Render Layer Offset", &renderLayerOffset))
						{
							inspect->SetTileLayerRenderLayerOffset(layerIndex, renderLayerOffset);
						}
					}

					ImGui::PopID();

					++layerIndex;
				}
			}
		}
	}
} // GEngineCore