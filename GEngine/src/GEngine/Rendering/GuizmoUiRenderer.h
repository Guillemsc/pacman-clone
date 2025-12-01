//
// Created by guillem on 7/11/25.
//

#ifndef GUIZMOUIRENDERER_H
#define GUIZMOUIRENDERER_H

#include <functional>
#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/Colors/Color01.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	struct CornersRect;
	class GEngineCoreApplication;

	class GuizmoUiRenderer
	{
	public:
		explicit GuizmoUiRenderer(GEngineCoreModules* modules);

		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

		void AddCircle(const glm::vec2& position, float radius, const Color01& color);
		void AddLineRect(const CornersRect& rect, float thickness, const Color01& color);
		void AddLine(const glm::vec2& start, const glm::vec2& end, float thickness, const Color01& color);

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;

	private:
		GEngineCoreModules* const _modules;

		LayeredRenderQueue _renderQueue;
	};
}

#endif //GUIZMOUIRENDERER_H
