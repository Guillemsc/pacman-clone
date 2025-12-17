//
// Created by guillem on 6/9/25.
//

#ifndef IMGUIEXTENSIONS_H
#define IMGUIEXTENSIONS_H

#include <string>

#include "imgui.h"

struct ImGuiInputTextCallbackData;

namespace GEngine
{
	class ImGuiExtensions
	{
	public:
		static bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0);
		static bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags = 0);

	private:
		static int InputTextCallback(ImGuiInputTextCallbackData* data);
	};
}

#endif //IMGUIEXTENSIONS_H
