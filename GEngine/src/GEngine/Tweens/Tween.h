//
// Created by guillem on 7/27/25.
//

#ifndef TWEEN_H
#define TWEEN_H

#include <memory>
#include <vector>

#include "ChildrenTweenSequenceMode.h"
#include "EasingType.h"

namespace GEngine
{
	class Tween
	{
	public:
		void Start();
		void Tick(float deltaTime);

		void AddChildren(const std::shared_ptr<Tween>& tween, ChildrenTweenSequenceMode tickMode = ChildrenTweenSequenceMode::APPEND);
		void SetEasing(EasingType easing);

		bool IsPlaying() const;

		void Kill();

	protected:
		void CompleteMain();

		virtual void OnSetEasing(EasingType easing) {}
		virtual void OnStart() {};
		virtual void OnTick(float deltaTime);

	private:
		void StartChildren();

		void RunNextChildTweens();

		void TickChildren(float deltaTime);
		void CompleteChildren();

	private:
		bool _started = false;
		bool _completed = false;

		bool _mainCompleted = false;
		bool _childrenCompleted = false;

		std::vector<std::tuple<std::shared_ptr<Tween>, ChildrenTweenSequenceMode>> _children;
		std::vector<std::int32_t> _childrenRunning;
		std::int32_t _biggestRunningIndex = 0;
	};
}

#endif //TWEEN_H
