//
// Created by guillem on 7/12/25.
//

#include "AnchorsUiTransformExample.h"

#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	void AnchorsUiTransformExample::Init()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();
		if (!entities) return;

		// Big square with bottom left and top right quads
		const std::shared_ptr<Entity> entity1 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform1 = entity1->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer1 = entity1->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer1->SetColor({0.5f, 0.5, 0.8});
		uiTransform1->SetAnchors({0.2, 0.2, 0.8, 0.8});
		uiTransform1->SetSizeDelta({0, 0});

		const std::shared_ptr<Entity> entity2 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform2 = entity2->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer2 = entity2->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer2->SetColor({0.8f, 0.8, 0.8});
		uiTransform2->SetAnchors({0, 0, 0, 0});
		uiTransform2->SetPivot({0, 0});
		entity2->SetParent(entity1);

		const std::shared_ptr<Entity> entity3 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform3 = entity3->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer3 = entity3->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer3->SetColor({0.8f, 0.8, 0.8});
		uiTransform3->SetAnchors({1, 1, 1, 1});
		uiTransform3->SetPivot({1, 1});
		entity3->SetParent(entity1);

		// Top square
		const std::shared_ptr<Entity> entity4 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform4 = entity4->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer4 = entity4->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer4->SetColor({0.8f, 0.5, 0.5});
		uiTransform4->SetAnchors({0.1, 1, 0.9, 1});
		uiTransform4->SetPivot({0.5, 1});
		uiTransform4->SetSizeDelta({0, 50});

		// Left square
		const std::shared_ptr<Entity> entity5 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform5 = entity5->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer5 = entity5->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer5->SetColor({0.5f, 0.8, 0.5});
		uiTransform5->SetAnchors({0, 0.1, 0, 0.9});
		uiTransform5->SetPivot({0, 0.5});
		uiTransform5->SetSizeDelta({50, 0});

		// Rotated squares
		const std::shared_ptr<Entity> entity6 = entities->AddUiEntity().lock();
		_uiTransform6 = entity6->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer6 = entity6->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer6->SetColor({0.2f, 0.2, 0.5});
		_uiTransform6->SetAnchors({1, 0, 1, 0});
		_uiTransform6->SetAnchoredPosition({-100, 100});
		_uiTransform6->SetSizeDelta({200, 50});
		_uiTransform6->SetRotation(-0.2f);

		const std::shared_ptr<Entity> entity7 = entities->AddUiEntity().lock();
		const std::shared_ptr<UiTransformComponent> uiTransform7 = entity7->GetUiTransform().lock();
		const std::shared_ptr<UiShapeRendererComponent> shapeRenderer7 = entity7->AddComponent<UiShapeRendererComponent>().lock();
		shapeRenderer7->SetColor({0.8f, 0.2, 0.5});
		uiTransform7->SetAnchors({0, 0, 0, 0});
		uiTransform7->SetPivot({0, 0});
		uiTransform7->SetSizeDelta({30, 30});
		entity7->SetParent(entity6);
	}

	void AnchorsUiTransformExample::Tick(const float deltaTime)
	{
		float rotation = _uiTransform6->GetRotation() + deltaTime;
		_uiTransform6->SetRotation(rotation);
	}

	void AnchorsUiTransformExample::Dispose()
	{

	}
}
