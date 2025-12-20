//
// Created by guillem on 7/27/25.
//

#ifndef INTERPOLATIONTWEEN_H
#define INTERPOLATIONTWEEN_H

#include <functional>

#include "Easing.h"
#include "EasingType.h"
#include "Tween.h"
#include "GEngine/Extensions/MathExtensions.h"

namespace GEngine
{
	template <class T>
	class InterpolationTween final : public Tween
	{
	public:
		InterpolationTween(
			std::function<T()> getter,
			std::function<void(T)> setter,
			T endValue,
			float duration
		);

	protected:
		void OnSetEasing(EasingType easing) override;
		void OnStart() override;
		void OnTick(float deltaTime) override;

	private:
		std::function<T()> _getter;
		std::function<void(T)> _setter;
		T _endValue;
		float _duration;

		EasingType _easingType = EasingType::LINEAR;

		T _startValue;
		float _currentTime = 0.0f;
		T _currentValue;
	};

	template<class T>
	InterpolationTween<T>::InterpolationTween(
		std::function<T()> getter,
		std::function<void(T)> setter,
		T endValue,
		const float duration
		)
	{
		_getter = getter;
		_setter = setter;
		_endValue = endValue;
		_duration = duration;
	}

	template<class T>
	void InterpolationTween<T>::OnSetEasing(const EasingType easing)
	{
		_easingType = easing;
	}

	template<class T>
	void InterpolationTween<T>::OnStart()
	{
		_startValue = _getter();
		_currentValue = _startValue;
		_currentTime = 0.0f;
	}

	template<class T>
	void InterpolationTween<T>::OnTick(const float deltaTime)
	{
		_currentTime += deltaTime;

		float progress = 1.0f;

		if (_duration > 0)
		{
			progress = MathExtensions::SafeDivide(_currentTime, _duration);
		}

		progress = Easing::GetEasingFunction(_easingType)(progress);
		_currentValue = MathExtensions::Lerp(_startValue, _endValue, progress);

		const bool completed = progress >= 1.0f;

		if (completed)
		{
			_currentValue = _endValue;
		}

		_setter(_currentValue);

		if (completed)
		{
			CompleteMain();
		}
	}
}

#endif //INTERPOLATIONTWEEN_H
