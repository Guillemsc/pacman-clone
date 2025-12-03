//
// Created by guillem on 12/2/25.
//

#ifndef COLLISIONSMODULE_H
#define COLLISIONSMODULE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "GEngine/Colliders2d/Contact2dData.h"

namespace GEngine
{
	class Collider2d;
	class GEngineCoreModules;
	class Entity;

	class Collisions2dModule
	{
	public:
		void Init(GEngineCoreModules* modules);
		void Tick();
		void Dispose();

		std::weak_ptr<Collider2d> AddCollider(const std::weak_ptr<Entity>& owner);
		void RemoveCollider(const std::weak_ptr<Collider2d>& collider);

		const std::unordered_map<std::shared_ptr<Collider2d>, std::vector<std::shared_ptr<Collider2d>>>& GetCurrentContacts();

	private:
		void CheckCollisions();

		bool DoesContactAlreadyExists(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with);
		void RegisterContact(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with);
		void RemoveContact(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with);
		void ClearContacts(const std::shared_ptr<Collider2d>& collider);
		bool DidContactHappenThisFrame(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with);

	private:
		GEngineCoreModules* _modules = nullptr;

		std::vector<std::shared_ptr<Collider2d>> _colliders;
		std::unordered_map<std::shared_ptr<Collider2d>, std::vector<std::shared_ptr<Collider2d>>> _currentContacts;

		std::unordered_map<std::shared_ptr<Collider2d>, std::vector<std::shared_ptr<Collider2d>>> _contactsThisFrame;
		std::vector<std::tuple<std::shared_ptr<Collider2d>, std::shared_ptr<Collider2d>>> _contactsToRemoveThisFrame;
	};
}

#endif //COLLISIONSMODULE_H
