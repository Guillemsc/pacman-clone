//
// Created by guillem on 12/17/25.
//

#include "UiTextRendererComponentInspectorEditor.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "GEngine/Editor/Extensions/ImGuiExtensions.h"

namespace GEngine
{
	void UiTextRendererComponentInspectorEditor::DrawSpecific(const std::shared_ptr<UiTextRendererComponent> &inspect)
	{
		std::string text = inspect->GetText();
		if (ImGuiExtensions::InputTextMultiline("Text", &text, {0, 100}))
		{
			inspect->SetText(text);
		}

		float size = inspect->GetSize();
		if (ImGui::DragFloat("Size", &size, 1))
		{
			inspect->SetSize(size);
		}

		ImGui::Text("Horizontal Alignment:");

		const HorizontalTextAlign horizontal = inspect->GetHorizontalAlign();

		if (DrawToolbarButton("Left", horizontal == HorizontalTextAlign::LEFT))
		{
			inspect->SetHorizontalAlign(HorizontalTextAlign::LEFT);
		}
		ImGui::SameLine();

		if (DrawToolbarButton("Center", horizontal == HorizontalTextAlign::CENTER))
		{
			inspect->SetHorizontalAlign(HorizontalTextAlign::CENTER);
		}
		ImGui::SameLine();

		if (DrawToolbarButton("Right", horizontal == HorizontalTextAlign::RIGHT))
		{
			inspect->SetHorizontalAlign(HorizontalTextAlign::RIGHT);
		}
		ImGui::SameLine();

		if (DrawToolbarButton("Justify", horizontal == HorizontalTextAlign::JUSTIFY))
		{
			inspect->SetHorizontalAlign(HorizontalTextAlign::JUSTIFY);
		}
		ImGui::SameLine();

		if (DrawToolbarButton("No Word Wrap", horizontal == HorizontalTextAlign::NO_WORD_WRAP))
		{
			inspect->SetHorizontalAlign(HorizontalTextAlign::NO_WORD_WRAP);
		}

		float wordSpacing = inspect->GetWordSpacing();
		if (ImGui::DragFloat("Word Spacing", &wordSpacing, 0.5f))
		{
			inspect->SetWordSpacing(wordSpacing);
		}
	}

	bool UiTextRendererComponentInspectorEditor::DrawToolbarButton(const char *label, const bool selected)
	{
		if (selected)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
		}

		const bool pressed = ImGui::Button(label);

		if (selected)
		{
			ImGui::PopStyleColor();
		}

		return pressed;
	}
}
