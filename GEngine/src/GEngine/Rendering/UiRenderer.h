//
// Created by guillem on 7/1/25.
//

#ifndef UIRENDERER_H
#define UIRENDERER_H

#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/RenderCommands/UiRendererCommand.h"
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

		void AddRect(
			std::int32_t layer,
			const glm::vec2 &position,
			float rotationRadians,
			const glm::vec2 &size,
			const glm::vec2& center,
			const Color01 &color
			);

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;
		glm::vec4 RectToRenderRect(const glm::vec4& rect) const;
		static float RotationToRenderRotation(float rotation);

	private:
		void AddCommand(std::int32_t layer, const UiRendererCommand& command);

		static void RenderCommand(const UiRendererCommand& command);
		static void RenderRectCommand(const RectUiRendererCommand& command);

	private:
		GEngineCoreModules* const _modules;

		std::map<std::int32_t, std::vector<UiRendererCommand>> _queue;
	};
}
#endif //UIRENDERER_H
