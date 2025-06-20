//
// Created by guillem on 6/20/25.
//

#include "TiledMapResourceInspectorEditor.h"

#include <format>

#include "imgui.h"

namespace GEngineCore
{
	void TiledMapResourceInspectorEditor::DrawSpecific(const std::shared_ptr<TiledMapResource> &inspect)
	{
		const std::shared_ptr<tmx::Map> rawMap = inspect->GetRawMap().lock();

		const std::vector<tmx::Tileset>& tilesets = rawMap->getTilesets();

		ImGui::Spacing();
		ImGui::CollapsingHeader("Tilesets", ImGuiTreeNodeFlags_Leaf);

		for (const auto& tileset : tilesets)
		{
			if (ImGui::CollapsingHeader(tileset.getName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text(std::format("Tile Size: X:{0} Y:{1}", tileset.getTileSize().x, tileset.getTileSize().y).c_str());
				ImGui::TextWrapped(std::format("Image Path: {0}", tileset.getImagePath()).c_str());
			}
		}

		const std::vector<tmx::Layer::Ptr>& layers = rawMap->getLayers();

		ImGui::Spacing();
		ImGui::CollapsingHeader("Layers", ImGuiTreeNodeFlags_Leaf);

		for (const auto& layer : layers)
		{
			if (ImGui::CollapsingHeader(layer->getName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text(std::format("Layer Size: X:{0} Y:{0}", layer->getSize().x,  layer->getSize().y).c_str());
			}
		}
	}
} // GEngineCore