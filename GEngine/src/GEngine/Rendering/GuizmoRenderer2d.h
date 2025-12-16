//
// Created by guillem on 12/1/25.
//

#ifndef GUIZMO2DRENDERER_H
#define GUIZMO2DRENDERER_H

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_set>

#include "LayeredRenderQueue.h"
#include "GEngine/RenderCommands/GuizmoRenderer2dCommand.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct CornersRect;
	struct Color01;
	class GEngineCoreModules;

	class GuizmoRenderer2d
	{
	public:
		explicit GuizmoRenderer2d(GEngineCoreModules* modules);

		void Render();

		void AddCircleLines(const glm::vec2& position, float radius, const Color01& color);
		void AddRect(const glm::vec2 &position, const glm::vec2 &size, float rotationRadians, const Color01 &color);
		void AddRectLines(const glm::vec2 &position, const glm::vec2 &size, float rotationRadians, float thickness, const Color01 &color);
		void AddLine(const glm::vec2& start, const glm::vec2& end, float thickness, const Color01& color);

		static glm::vec2 PositionToRenderPosition(const glm::vec2& position);
		static float RotationToRenderRotation(float rotation);

	private:
		void AddCommand(std::int32_t layer, const GuizmoRenderer2dCommand& command);

		static void RenderCommand(const GuizmoRenderer2dCommand& command);
		static void RenderLineCommand(const LineGuizmoRenderer2dCommand& command);
		static void RenderRectCommand(const RectGuizmoRenderer2dCommand& command);
		static void RenderRectLinesCommand(const RectLinesGuizmoRenderer2dCommand& command);
		static void RenderCircleLinesCommand(const CircleLinesGuizmoRenderer2dCommand& command);

	private:
		GEngineCoreModules* const _modules;

		std::map<std::int32_t, std::vector<GuizmoRenderer2dCommand>> _queue;
	};
}

#endif //GUIZMO2DRENDERER_H
