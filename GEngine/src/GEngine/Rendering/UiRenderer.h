//
// Created by guillem on 7/1/25.
//

#ifndef UIRENDERER_H
#define UIRENDERER_H

#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	class UiRenderer
	{
	public:
		explicit UiRenderer(GEngineCoreModules* modules);

		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;
		glm::vec4 RectToRenderRect(const glm::vec4& rect) const;

	private:
		GEngineCoreModules* const _modules;

		LayeredRenderQueue _renderQueue;
	};
}
#endif //UIRENDERER_H
