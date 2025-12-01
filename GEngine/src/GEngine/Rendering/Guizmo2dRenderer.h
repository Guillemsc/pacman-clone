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
#include "glm/vec2.hpp"

namespace GEngine
{
	struct CornersRect;
	struct Color01;
	class GEngineCoreModules;

	class Guizmo2dRenderer
	{
	public:
		explicit Guizmo2dRenderer(GEngineCoreModules* modules);

		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

		void AddCircle(const glm::vec2& position, float radius, const Color01& color);
		void AddRect(const glm::vec2 &position, const glm::vec2 &size, const Color01 &color);
		void AddLine(const glm::vec2& start, const glm::vec2& end, float thickness, const Color01& color);

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;

		void BeginLayer(const std::string& layer);
		void EndLayer();
		bool IsCurrentLayerEnabled() const;

	private:
		GEngineCoreModules* const _modules;

		LayeredRenderQueue _renderQueue;

		std::unordered_set<std::string> _enabledLayers;
		std::string _currentLayer;
	};
}

#endif //GUIZMO2DRENDERER_H
