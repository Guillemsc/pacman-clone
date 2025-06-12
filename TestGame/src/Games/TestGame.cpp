//
// Created by guillem on 6/7/25.
//

#include "TestGame.h"

#include "Components/Shape2dRendererComponent.h"
#include "Components/Texture2dRendererComponent.h"
#include "Components/TransformComponent.h"
#include "Core/GEngineCoreApplication.h"
#include "Modules/EntitiesModule.h"
#include "Modules/GameModule.h"
#include "Resources/TextureResource.h"

TestGame::~TestGame()
{

}

void TestGame::Init()
{
	auto app = _app.lock();
	if (!app) return;

	std::shared_ptr<GEngineCore::EntitiesModule> entities = app->Entities().lock();
	std::shared_ptr<GEngineCore::GameModule> game = app->Game().lock();
	std::shared_ptr<GEngineCore::ResourcesModule> resources = app->Resources().lock();

	_entity1 = entities->AddEntity();
	auto entity2 = entities->AddEntity();
	//auto entity3 = entities->AddEntity();

	_entity1.lock()->GetTransform().lock()->SetPosition({0, 0, 0});
	entity2.lock()->GetTransform().lock()->SetPosition({0, 100, 0});

	entity2.lock()->SetParent(_entity1);
	//entity3.lock()->SetParent(entity2);

	_entity1.lock()->AddComponent<GEngineCore::Shape2dRendererComponent>();
	_entity1.lock()->AddComponent<GEngineCore::Texture2dRendererComponent>();
	entity2.lock()->AddComponent<GEngineCore::Shape2dRendererComponent>();
	//std::weak_ptr<GEngineCore::Texture2dRendererComponent> textureComponent = entity3.lock()->AddComponent<GEngineCore::Texture2dRendererComponent>();

	//entity2.lock()->GetTransform().lock()->SetPosition({100, 100, 0});
	//entity3.lock()->GetTransform().lock()->SetLocalPosition({30, 00, 0});
	_entity1.lock()->GetTransform().lock()->SetLocalRotationEulerDegreesZ(30);

	//std::weak_ptr<GEngineCore::TextureResource> texture = resources->GetResource<GEngineCore::TextureResource>("proxy-image.png");
	//textureComponent.lock()->SetTexture(texture);
}

void TestGame::Tick()
{
	float rotation = _entity1.lock()->GetTransform().lock()->GetLocalRotationEulerDegreesZ();

	if (IsKeyDown(KEY_RIGHT))
	{
		rotation += 2.0f;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		rotation -= 2.0f;
	}

	_entity1.lock()->GetTransform().lock()->SetLocalRotationEulerDegreesZ(rotation);
}

void TestGame::Dispose()
{

}



