//
// Created by guillem on 7/12/25.
//

#include "ExamplesModule.h"

#include "GEngine/Data/ExampleData.h"
#include "GEngine/Examples/Tweens/DevelopmentTweensExample.h"
#include "GEngine/Examples/UiTransform/AnchorsUiTransformExample.h"

namespace GEngine
{
	ExamplesModule::ExamplesModule()
	{
		_examples.push_back({"Anchors Ui Transform", std::make_shared<AnchorsUiTransformExample>()});
		_examples.push_back({"Development Tweens", std::make_shared<DevelopmentTweensExample>()});
	}

	void ExamplesModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	const std::vector<ExampleData>& ExamplesModule::GetExamples() const
	{
		return _examples;
	}
} // GEngine