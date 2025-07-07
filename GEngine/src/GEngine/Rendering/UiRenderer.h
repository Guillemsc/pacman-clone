//
// Created by guillem on 7/1/25.
//

#ifndef UIRENDERER_H
#define UIRENDERER_H

#include <memory>

#include "LayeredRenderQueue.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "glm/vec4.hpp"

namespace GEngine
{
	class UiRenderer
	{
	public:
		UiRenderer(const std::weak_ptr<GEngineCoreApplication> &appPtr);

		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

		glm::vec4 RectToRenderRect(const glm::vec4& rect) const;

	private:
		std::weak_ptr<GEngineCoreApplication> _appPtr;

		LayeredRenderQueue _renderQueue;
	};
}
#endif //UIRENDERER_H
