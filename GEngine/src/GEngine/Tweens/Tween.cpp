//
// Created by guillem on 7/27/25.
//

#include "Tween.h"

namespace GEngine
{
	void Tween::Start()
	{
		if (_started) return;

		_started = true;
		_completed = false;
		_mainCompleted = false;
		_childrenCompleted = false;

		OnStart();
		StartChildren();
	}

	void Tween::Tick(const float deltaTime)
	{
		if (!_started) return;
		if (_completed) return;

		if (!_mainCompleted)
		{
			OnTick(deltaTime);
		}

		if (!_childrenCompleted)
		{
			TickChildren(deltaTime);
		}
	}

	void Tween::AddChildren(const std::shared_ptr<Tween> &tween, const ChildrenTweenTickMode tickMode)
	{
		if (_started) return;
		_children.push_back(std::make_tuple(tween, tickMode));
	}

	void Tween::SetEasing(const EasingType easing)
	{
		OnSetEasing(easing);
	}

	void Tween::CompleteMain()
	{
		_mainCompleted = true;

		if (_childrenCompleted)
		{
			_completed = true;
		}
	}

	void Tween::StartChildren()
	{
		_biggestRunningIndex = 0;

		RunNextChildTweens();

		if (_childrenRunning.size() == 0)
		{
			CompleteChildren();
		}
	}

	void Tween::RunNextChildTweens()
	{
		for (std::int32_t i = _biggestRunningIndex; i < _children.size(); i++)
		{
			const auto& child = _children[i];
			const std::shared_ptr<Tween> tween = std::get<std::shared_ptr<Tween>>(child);
			const ChildrenTweenTickMode mode = std::get<ChildrenTweenTickMode>(child);

			bool shouldBreak = false;

			switch (mode)
			{
				case ChildrenTweenTickMode::APPEND:
				{
					if (_childrenRunning.size() > 0)
					{
						shouldBreak = true;
					}
					else
					{
						tween->Start();
						_childrenRunning.push_back(i);
						_biggestRunningIndex = i;
					}
					break;
				}

				case ChildrenTweenTickMode::JOIN:
				{
					tween->Start();
					_childrenRunning.push_back(i);
					_biggestRunningIndex = i;
					break;
				}
			}

			if (shouldBreak)
			{
				break;
			}
		}
	}

	void Tween::TickChildren(const float deltaTime)
	{
		for (std::int32_t i = _childrenRunning.size() - 1; i >= 0; --i)
		{
			const int childIndex = _childrenRunning[i];
			const auto& child = _children[childIndex];
			const std::shared_ptr<Tween> tween = std::get<std::shared_ptr<Tween>>(child);

			tween->Tick(deltaTime);

			if (tween->_completed)
			{
				_childrenRunning.erase(_childrenRunning.begin() + i);
			}
		}

		if (_childrenRunning.size() == 0)
		{
			++_biggestRunningIndex;

			if (_biggestRunningIndex < _children.size())
			{
				RunNextChildTweens();
			}
			else
			{
				CompleteChildren();
			}
		}
	}

	void Tween::CompleteChildren()
	{
		_childrenCompleted = true;

		if (_mainCompleted)
		{
			_completed = true;
		}
	}
}
