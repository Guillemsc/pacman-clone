//
// Created by guillem on 6/9/25.
//

#include "ImGuiExtensions.h"

#include <string>

#include "imgui.h"

namespace GEngineCore
{
	bool ImGuiExtensions::InputText(const char *label, std::string *str, ImGuiInputTextFlags flags)
	{
		IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
		flags |= ImGuiInputTextFlags_CallbackResize;
		return ImGui::InputText(label, str->data(), str->capacity() + 1, flags, InputTextCallback, str);
	}

	int ImGuiExtensions::InputTextCallback(ImGuiInputTextCallbackData *data)
	{
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			std::string* str = static_cast<std::string*>(data->UserData);
			str->resize(data->BufTextLen);
			data->Buf = (char*)str->c_str();
		}

		return 0;
	}
} // GEngineCore