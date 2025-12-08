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
	class GEngineCoreModules;
	class GEngineCoreApplication;
	class JsonData;

	class WindowModule
	{
	public:
		void ApplyConfig(const JsonData& config);
		void Init(GEngineCoreModules* modules);
		bool CanRun();
		void Tick();
		void Dispose();

		[[nodiscard]] glm::i32vec2 GetWindowSize() const;

	private:
		void CheckWindowSizeChanged();
		void OnWindowSizeChanged() const;

	private:
		GEngineCoreModules* _modules = nullptr;

		std::string _titleInitialValue = "GEngine";
		glm::i32vec2 _sizeInitialValue = glm::i32vec2(1200, 850);
		bool _fullscreenInitialValue = false;
		bool _resizableInitialValue = true;
		bool _vSyncInitialValue = false;
		int _targetFramesInitialValue = 0;

		glm::i32vec2 _previousWindowSize = Vec2Extensions::Int32Zero;
	};
}

#endif //WINDOWMODULE_H
