//
// Created by guillem on 12/3/25.
//

#include "Collisions2dEditorWindow.h"

#include "EditorWindow.h"
#include "imgui.h"
#include "GEngine/Colliders2d/Collider2d.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/Collisions2dModule.h"

namespace GEngine
{
	Collisions2dEditorWindow::Collisions2dEditorWindow(GEngineCoreModules *modules)
		: EditorWindow(modules, "Collisions 2d")
	{

	}

	void Collisions2dEditorWindow::DrawWindowContent()
	{
		const std::unordered_map<std::shared_ptr<Collider2d>, std::vector<std::shared_ptr<Collider2d>>>& currentContacts
			= _modules->collisions2d->GetCurrentContacts();

		if (currentContacts.empty())
		{
			ImGui::Text("No contacts to be shown");
			return;
		}

		for (auto it = currentContacts.begin(); it != currentContacts.end(); ++it)
		{
			const std::shared_ptr<Collider2d>& current = it->first;
			const std::shared_ptr<Entity> currentEntity = current->GetOwner().lock();

			ImGui::Text("%s", currentEntity->GetName().c_str());

			const std::vector<std::shared_ptr<Collider2d>>& otherColliders = it->second;

			ImGui::Indent(8);

			for (const std::shared_ptr<Collider2d>& other : otherColliders)
			{
				const std::shared_ptr<Entity> otherEntity = other->GetOwner().lock();

				ImGui::BulletText("%s", otherEntity->GetName().c_str());
			}

			ImGui::Unindent(8);

			ImGui::Separator();
			ImGui::Spacing();
		}
	}
}
