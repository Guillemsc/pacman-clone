//
// Created by guillem on 7/26/25.
//

#ifndef METACONTEXT_H
#define METACONTEXT_H

#include <memory>

#include "Context.h"
#include "GEngine/Entities/Entity.h"

namespace PacMan
{
	class Coroutine;

	class MetaContext : public Context
	{
	public:
		MetaContext();

		tokoro::Async<void> OnLoadAsync() override;
		void OnDispose() override;

	private:
		void WhenPlayButtonClicked();
	};
}

#endif //METACONTEXT_H
