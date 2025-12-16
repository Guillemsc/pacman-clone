//
// Created by guillem on 7/11/25.
//

#ifndef GUIZMOUIRENDERER_H
#define GUIZMOUIRENDERER_H

#include <functional>
#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/Colors/Color01.h"
#include "GEngine/RenderCommands/GuizmoUiRendererCommand.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	class GEngineCoreModules;
	struct CornersRect;
	class GEngineCoreApplication;

	class GuizmoUiRenderer
	{
	public:
		explicit GuizmoUiRenderer(GEngineCoreModules* modules);

		void Render();

		void AddLine(const glm::vec2& start, const glm::vec2& end, float thickness, const Color01& color);
		void AddCornersRectLines(const CornersRect& rect, float thickness, const Color01& color);
		void AddCircleLines(const glm::vec2& position, float radius, const Color01& color);

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;

	private:
		void AddCommand(std::int32_t layer, const GuizmoUiRendererCommand& command);

		void RenderCommand(const GuizmoUiRendererCommand& command) const;
		void RenderLineCommand(const LineGuizmoUiRendererCommand& command) const;
		void RenderRectLinesCommand(const CornersRectLinesGuizmoUiRendererCommand& command) const;
		void RenderCircleLinesCommand(const CircleLinesGuizmoUiRendererCommand& command) const;

	private:
		GEngineCoreModules* const _modules;

		LayeredRenderQueue _renderQueue;

		std::map<std::int32_t, std::vector<GuizmoUiRendererCommand>> _queue;
	};
}

#endif //GUIZMOUIRENDERER_H
