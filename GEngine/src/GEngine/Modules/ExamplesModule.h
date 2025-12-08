//
// Created by guillem on 7/12/25.
//

#ifndef EXAMPLESMODULE_H
#define EXAMPLESMODULE_H

#include <memory>
#include <vector>

#include "GEngine/Data/ExampleData.h"

namespace GEngine
{
	class GEngineCoreApplication;

	class ExamplesModule
	{
	public:
		ExamplesModule();

		void Init(GEngineCoreModules* modules);

		[[nodiscard]] const std::vector<ExampleData>& GetExamples() const;

	private:
		GEngineCoreModules* _modules = nullptr;

		std::vector<ExampleData> _examples;
	};

}

#endif //EXAMPLESMODULE_H
