//
// Created by guillem on 6/7/25.
//

#ifndef WINDOWMODULE_H
#define WINDOWMODULE_H

#include <memory>

#include "GEngine/Extensions/Vec2Extensions.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class GEngineCoreApplication;

	class WindowModule
	{
	public:
		void Init(const std::weak_ptr<GEngineCoreApplication>& appPtr);
		bool CanRun();
		void Tick();
		void Dispose();

		glm::i32vec2 GetWindowSize() const;

	private:
		void CheckWindowSizeChanged();
		void OnWindowSizeChanged() const;

	private:
		std::weak_ptr<GEngineCoreApplication> _appPtr;

		glm::i32vec2 _previousWindowSize = Vec2Extensions::Int32Zero;
	};
}

#endif //WINDOWMODULE_H
