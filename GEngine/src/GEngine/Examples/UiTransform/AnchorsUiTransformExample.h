//
// Created by guillem on 7/12/25.
//

#ifndef ANCHORSUITRANSFORMEXAMPLE_H
#define ANCHORSUITRANSFORMEXAMPLE_H

#include <vector>

#include "GEngine/Games/Game.h"

namespace GEngine
{
	class UiTransformComponent;

	class AnchorsUiTransformExample final : public Game
	{
	public:
		AnchorsUiTransformExample();

		void Init() override;
		void Tick(float deltaTime) override;
		void Dispose() override;

	private:
		std::shared_ptr<UiTransformComponent> _uiTransform6;
	};
}

#endif //ANCHORSUITRANSFORMEXAMPLE_H
