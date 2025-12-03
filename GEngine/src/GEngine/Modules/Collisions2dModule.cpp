//
// Created by guillem on 12/2/25.
//

#include "Collisions2dModule.h"

#include "GEngine/Colliders2d/Collider2d.h"
#include "GEngine/Colliders2d/Collision2dData.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Extensions/UnorderedMapExtensions.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	void Collisions2dModule::Init(GEngineCoreModules *modules)
	{
		_modules = modules;
	}

	void Collisions2dModule::Tick()
	{
		CheckCollisions();
	}

	void Collisions2dModule::Dispose()
	{
		_colliders.clear();
	}

	std::weak_ptr<Collider2d> Collisions2dModule::AddCollider(const std::weak_ptr<Entity>& owner)
	{
		const std::shared_ptr<Collider2d> collider2d = std::make_shared<Collider2d>(owner);
		_colliders.push_back(collider2d);
		return collider2d;
	}

	void Collisions2dModule::RemoveCollider(const std::weak_ptr<Collider2d> &collider)
	{
		const std::shared_ptr<Collider2d> lCollider = collider.lock();
		if (!lCollider) return;

		ClearContacts(lCollider);

		VectorExtensions::Remove(_colliders, lCollider);
	}

	void Collisions2dModule::CheckCollisions()
	{
		const std::uint32_t collidersCount = _colliders.size();

		for (std::uint32_t i = 0; i < collidersCount; ++i)
		{
			const std::shared_ptr<Collider2d>& a = _colliders[i];

			for (std::uint32_t j = i + 1; j < collidersCount; ++j)
			{
				const std::shared_ptr<Collider2d>& b = _colliders[j];

				const bool aCanCollideWithB = a->CanLayersCollide(b.get());
				const bool bCanCollideWithA = b->CanLayersCollide(a.get());

				const bool canCollideAny = aCanCollideWithB || bCanCollideWithA;
				if (!canCollideAny) continue;

				const bool collided = a->Intersects(b.get());
				if (!collided) continue;

				if (aCanCollideWithB)
				{
					AddContact(a, b);
				}

				if (bCanCollideWithA)
				{
					AddContact(b, a);
				}
			}
		}
	}

	bool Collisions2dModule::ContactAlreadyExists(
		const std::shared_ptr<Collider2d>& collider,
		const std::shared_ptr<Collider2d>& with
		) 
	{
		const auto optional = UnorderedMapExtensions::GetValueReference(_currentContacts, collider);
		if (!optional.has_value()) return false;

		const std::vector<std::shared_ptr<Collider2d>>& contacts = optional.value().get();

		for (const std::shared_ptr<Collider2d>& contact : contacts)
		{
			if (contact == with)
			{
				return true;
			}
		}

		return false;
	}

	void Collisions2dModule::AddContact(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with)
	{
		const bool contactAlreadyExists = ContactAlreadyExists(collider, with);

		const Collision2dData collisionData = { collider, with };

		if (contactAlreadyExists)
		{
			collider->_onCollisionStay.Invoke(collisionData);
			return;
		}

		_currentContacts[collider].push_back(with);

		collider->_onCollisionStart.Invoke(collisionData);
	}

	void Collisions2dModule::RemoveContact(const std::shared_ptr<Collider2d>& collider, const std::shared_ptr<Collider2d>& with)
	{
		const auto it = _currentContacts.find(collider);
		if (it == _currentContacts.end()) return;

		const bool removed = VectorExtensions::Remove(it->second, with);
		if (!removed) return;

		const Collision2dData collisionData = { collider, with };
		collider->_onCollisionEnd.Invoke(collisionData);
	}

	void Collisions2dModule::ClearContacts(const std::shared_ptr<Collider2d> &collider)
	{
		const auto optional = UnorderedMapExtensions::GetValueReference(_currentContacts, collider);

		if (optional.has_value())
		{
			const std::vector<std::shared_ptr<Collider2d>>& contacts = optional.value().get();

			for (std::shared_ptr<Collider2d> contacting : contacts)
			{
				RemoveContact(collider, contacting);
				RemoveContact(contacting, collider);
			}
		}

		UnorderedMapExtensions::RemoveKey(_currentContacts, collider);
	}
}
