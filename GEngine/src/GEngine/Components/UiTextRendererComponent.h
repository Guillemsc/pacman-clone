//
// Created by guillem on 7/26/25.
//

#ifndef UITEXTRENDERERCOMPONENT_H
#define UITEXTRENDERERCOMPONENT_H

#include "Component.h"
#include "GEngine/Text/HorizontalTextAlign.h"
#include "GEngine/Text/VerticalTextAlign.h"

namespace GEngine
{
	class FontResource;

	class UiTextRendererComponent final : public Component
	{
		REGISTER_COMPONENT(UiTextRendererComponent)

	public:
		explicit UiTextRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		std::string GetText() const;
		void SetText(const std::string& text);

		float GetSize() const;
		void SetSize(float size);

		HorizontalTextAlign GetHorizontalAlign() const;
		void SetHorizontalAlign(HorizontalTextAlign horizontalAlign);

		VerticalTextAlign GetVerticalAlign() const;
		void SetVerticalAlign(VerticalTextAlign verticalAlign);

		float GetWordSpacing() const;
		void SetWordSpacing(float wordSpacing);

	private:
		std::weak_ptr<FontResource> _fontResource;

		std::string _text = "Text";
		float _size = 1.0f;
		HorizontalTextAlign _horizontalAlign = HorizontalTextAlign::LEFT;
		VerticalTextAlign _verticalAlign = VerticalTextAlign::TOP;
		float _wordSpacing = 2.0f;

	};
}

#endif //UITEXTRENDERERCOMPONENT_H
