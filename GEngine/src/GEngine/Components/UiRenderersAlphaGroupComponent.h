//
// Created by guillem on 12/19/25.
//

#ifndef UIRENDERERSALPHAGROUPCOMPONENT_H
#define UIRENDERERSALPHAGROUPCOMPONENT_H

#include "Component.h"

namespace GEngine
{
	class UiRenderersAlphaGroupComponent final : public Component
	{
		REGISTER_COMPONENT(UiRenderersAlphaGroupComponent)

	public:
		UiRenderersAlphaGroupComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void SetAlpha(float alpha) const;
		float GetAlpha() const;

	private:
		std::shared_ptr<Property<float>> _alpha;
	};
}

#endif //UIRENDERERSALPHAGROUPCOMPONENT_H
