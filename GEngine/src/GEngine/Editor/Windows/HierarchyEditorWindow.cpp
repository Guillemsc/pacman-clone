//
// Created by guillem on 6/9/25.
//

#include "HierarchyEditorWindow.h"

#include <stack>

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	HierarchyEditorWindow::HierarchyEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Hierarchy")
	{
	}

	void HierarchyEditorWindow::DrawWindowContent()
	{
		const std::shared_ptr<GEngineObject> selectedObject = _modules->editor->GetSelectedObject().lock();

		const std::vector<std::weak_ptr<Entity>>& rootEntities = _modules->entities->GetRootEntities();

		_stack.clear();

		for (auto it = rootEntities.begin(); it != rootEntities.end(); ++it)
		{
			const std::shared_ptr<Entity> entity = it->lock();
			if (!entity) continue;

			_stack.emplace_back(entity, 0);
		}

		if (ImGui::Button("Add Entity"))
		{
			_modules->entities->AddWorldEntity();
		}

		int currentDepth = 0;

		while (!_stack.empty())
		{
			const auto [node, depth] = _stack.front();
			_stack.erase(_stack.begin());

			if (currentDepth > depth)
			{
				ImGui::TreePop();
			}

			const std::vector<std::weak_ptr<Entity>>& children = node->GetChildren();

			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

			if (children.empty())
			{
				flags |= ImGuiTreeNodeFlags_Leaf;
			}

			if (selectedObject)
			{
				const bool isSelected = node.get() == selectedObject.get();

				if (isSelected)
				{
					flags |= ImGuiTreeNodeFlags_Selected;
				}
			}

			const bool isActiveInHierarchy = node->IsActiveInHierarchy();

			if (!isActiveInHierarchy)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));  // Grey color
			}

			ImGui::PushID(node->GetId());

			if (ImGui::TreeNodeEx(node->GetName().c_str(), flags))
			{
				if (children.empty())
				{
					ImGui::TreePop();
				}
				else
				{
					for (auto it = children.begin(); it != children.end(); ++it)
					{
						const std::shared_ptr<Entity> child = it->lock();
						if (!child) continue;

						_stack.insert(_stack.begin(), { child, depth + 1 });
					}
				}
			}

			if (!isActiveInHierarchy)
			{
				ImGui::PopStyleColor();
			}

			DrawRightClickContextMenu(_modules->entities, node);
			DrawLeftClickContextMenu(_modules->editor, node);

			currentDepth = depth;

			ImGui::PopID();
		}

		while (currentDepth > 0)
		{
			--currentDepth;
			ImGui::TreePop();
		}
	}

	void HierarchyEditorWindow::DrawRightClickContextMenu(
		EntitiesModule* entities,
		const std::shared_ptr<Entity>& entity
		)
	{
		// Check if the tree node was right-clicked
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("NodeContextMenu");
		}

		// Create the popup context menu
		if (ImGui::BeginPopup("NodeContextMenu"))
		{
			if (ImGui::MenuItem("Delete"))
			{
				entities->RemoveEntity(entity);
			}
			if (ImGui::MenuItem("Rename"))
			{
				// Handle rename action
			}
			ImGui::EndPopup();
		}
	}

	void HierarchyEditorWindow::DrawLeftClickContextMenu(
		EditorModule* editor,
		const std::shared_ptr<Entity> &entity)
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			editor->SetSelectedObject(entity);
		}
	}
} // GEngineCore