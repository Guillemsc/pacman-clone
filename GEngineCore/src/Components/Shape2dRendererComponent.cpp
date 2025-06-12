//
// Created by guillem on 6/8/25.
//

#include "Texture2dRendererComponent.h"

#include "raylib.h"
#include "TransformComponent.h"
#include "Modules/RenderingModule.h"

namespace GEngineCore
{
	Texture2dRendererComponent::Texture2dRendererComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{

	}

	void Texture2dRendererComponent::OnTick()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		float positionX = transform->GetPosition().x;
		float positionY = -transform->GetPosition().y;
		float rotation = transform->GetRotationEulerDegreesZ();

		rendering->Render2D().lock()->Add(0, [positionX, positionY, rotation]()
		{
			Vector2 size = {20, 20};
			Vector2 center = { size.x * 0.5f, size.y * 0.5f };

			Rectangle rectangle = {
				positionX - center.x,
				positionY - center.y,
				size.x,
				size.y,
			};

			DrawRectanglePro(rectangle, center, rotation, RED);
		});
	}

	void Texture2dRendererComponent::OnDestroy()
	{

	}
} // GEngineCore