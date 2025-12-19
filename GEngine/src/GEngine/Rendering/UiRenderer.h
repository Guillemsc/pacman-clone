//
// Created by guillem on 7/1/25.
//

#ifndef UIRENDERER_H
#define UIRENDERER_H

#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/RenderCommands/UiRendererCommand.h"
#include "GEngine/Text/HorizontalTextAlign.h"
#include "GEngine/Text/VerticalTextAlign.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	class GEngineCoreModules;

	class UiRenderer
	{
	public:
		explicit UiRenderer(GEngineCoreModules* modules);

		void Render();

		void AddTexture(
			std::int32_t layer,
			const Texture2D& texture,
			const glm::vec2 &position,
			float rotationRadians,
			const glm::vec2 &size,
			const glm::vec2& center,
			const Color01 &color
			);

		void AddRect(
			std::int32_t layer,
			const glm::vec2 &position,
			float rotationRadians,
			const glm::vec2 &size,
			const glm::vec2& center,
			const Color01 &color
			);

		void AddText(
			std::int32_t layer,
			FontResource* font,
			const std::string_view& text,
			const glm::vec2 &position,
			float rotationRadians,
			const glm::vec2 &size,
			const glm::vec2& pivot,
			float wordSpacing,
			const Color01 &color,
			HorizontalTextAlign horizontalAlign,
			VerticalTextAlign verticalAlign
			);

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;
		glm::vec2 PivotToRenderPivot(const glm::vec2& pivot) const;
		glm::vec4 RectToRenderRect(const glm::vec4& rect) const;
		static float RotationToRenderRotation(float rotation);

	private:
		void AddCommand(std::int32_t layer, const UiRendererCommand& command);

		void RenderCommand(const UiRendererCommand& command);
		void RenderTextureCommand(const TextureUiRendererCommand& command) const;
		void RenderRectCommand(const RectUiRendererCommand& command) const;
		void RenderTextCommand(const TextUiRendererCommand& command);

	private:
		GEngineCoreModules* const _modules;

		std::map<std::int32_t, std::vector<UiRendererCommand>> _queue;
	};
}
#endif //UIRENDERER_H
