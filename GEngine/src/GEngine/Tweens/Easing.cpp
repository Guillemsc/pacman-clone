//
// Created by guillem on 7/27/25.
//

#include "Easing.h"

#include <complex>
#include <numbers>

namespace GEngine
{
	Easing::EasingFunction Easing::GetEasingFunction(const EasingType easing)
	{
		switch (easing)
		{
			default:
			case EasingType::LINEAR:
				return EaseLinear;
			case EasingType::IN_SINE:
				return EaseInSine;
			case EasingType::OUT_SINE:
				return EaseOutSine;
			case EasingType::IN_OUT_SINE:
				return EaseInOutSine;
			case EasingType::IN_QUAD:
				return EaseInQuad;
			case EasingType::OUT_QUAD:
				return EaseOutQuad;
			case EasingType::IN_OUT_QUAD:
				return EaseInOutQuad;
			case EasingType::IN_CUBIC:
				return EaseInCubic;
			case EasingType::OUT_CUBIC:
				return EaseOutCubic;
			case EasingType::IN_OUT_CUBIC:
				return EaseInOutCubic;
			case EasingType::IN_QUART:
				return EaseInQuart;
			case EasingType::OUT_QUART:
				return EaseOutQuart;
			case EasingType::IN_OUT_QUART:
				return EaseInOutQuart;
			case EasingType::IN_QUINT:
				return EaseInQuint;
			case EasingType::OUT_QUINT:
				return EaseOutQuint;
			case EasingType::IN_OUT_QUINT:
				return EaseInOutQuint;
			case EasingType::IN_EXPO:
				return EaseInExpo;
			case EasingType::OUT_EXPO:
				return EaseOutExpo;
			case EasingType::IN_OUT_EXPO:
				return EaseInOutExpo;
			case EasingType::IN_CIRC:
				return EaseInCirc;
			case EasingType::OUT_CIRC:
				return EaseOutCirc;
			case EasingType::IN_OUT_CIRC:
				return EaseInOutCirc;
			case EasingType::IN_BACK:
				return EaseInBack;
			case EasingType::OUT_BACK:
				return EaseOutBack;
			case EasingType::IN_OUT_BACK:
				return EaseInOutBack;
			case EasingType::IN_ELASTIC:
				return EaseInElastic;
			case EasingType::OUT_ELASTIC:
				return EaseOutElastic;
			case EasingType::IN_OUT_ELASTIC:
				return EaseInOutElastic;
			case EasingType::IN_BOUNCE:
				return EaseInBounce;
			case EasingType::OUT_BOUNCE:
				return EaseOutBounce;
			case EasingType::IN_OUT_BOUNCE:
				return EaseInOutBounce;
		}
	}

	float Easing::EaseLinear(const float t)
	{
		return t;
	}

	float Easing::EaseInSine(const float t)
	{
		return std::sin(1.5707963 * t);
	}

	float Easing::EaseOutSine(const float t)
	{
		return 1 + std::sin(1.5707963 * (t - 1));
	}

	float Easing::EaseInOutSine(const float t)
	{
		return 0.5 * (1 + std::sin(3.1415926 * (t - 0.5)));
	}

	float Easing::EaseInQuad(const float t)
	{
		return t * t;
	}

	float Easing::EaseOutQuad(const float t)
	{
		return t * (2 - t);
	}

	float Easing::EaseInOutQuad(float t)
	{
		return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
	}

	float Easing::EaseInCubic(float t)
	{
		return t * t * t;
	}

	float Easing::EaseOutCubic(float t)
	{
		return 1 + (--t) * t * t;
	}

	float Easing::EaseInOutCubic(float t)
	{
		return t < 0.5 ? 4 * t * t * t : 1 + (--t - 1) * (2 * (--t)) * (2 * t);
	}

	float Easing::EaseInQuart(float t)
	{
		t *= t;
		return t * t;
	}

	float Easing::EaseOutQuart(float t)
	{
		t = (--t) * t;
		return 1 - t * t;
	}

	float Easing::EaseInOutQuart(float t)
	{
		if( t < 0.5 )
		{
			t *= t;
			return 8 * t * t;
		}

		t = (--t) * t;
		return 1 - 8 * t * t;
	}

	float Easing::EaseInQuint(float t)
	{
		float t2 = t * t;
		return t * t2 * t2;
	}

	float Easing::EaseOutQuint(float t)
	{
		float t2 = (--t) * t;
		return 1 + t * t2 * t2;
	}

	float Easing::EaseInOutQuint(float t)
	{
		float t2;

		if(t < 0.5)
		{
			t2 = t * t;
			return 16 * t * t2 * t2;
		}

		t2 = (--t) * t;
		return 1 + 16 * t * t2 * t2;
	}

	float Easing::EaseInExpo(float t)
	{
		return (std::pow( 2, 8 * t ) - 1) / 255;
	}

	float Easing::EaseOutExpo(float t)
	{
		return 1 - std::pow(2, -8 * t);
	}

	float Easing::EaseInOutExpo(float t)
	{
		if(t < 0.5)
		{
			return (std::pow(2, 16 * t) - 1) / 510;
		}

		return 1 - 0.5 * std::pow(2, -16 * (t - 0.5));
	}

	float Easing::EaseInCirc(float t)
	{
		return 1 - std::sqrt(1 - t);
	}

	float Easing::EaseOutCirc(float t)
	{
		return std::sqrt( t );
	}

	float Easing::EaseInOutCirc(float t)
	{
		if(t < 0.5)
		{
			return (1 - std::sqrt( 1 - 2 * t )) * 0.5;
		}

		return (1 + std::sqrt( 2 * t - 1 )) * 0.5;
	}

	float Easing::EaseInBack(float t)
	{
		return t * t * (2.70158 * t - 1.70158);
	}

	float Easing::EaseOutBack(float t)
	{
		return 1 + (--t) * t * (2.70158 * t + 1.70158);
	}

	float Easing::EaseInOutBack(float t)
	{
		if( t < 0.5 )
		{
			return t * t * (7 * t - 2.5) * 2;
		}

		return 1 + (--t) * t * 2 * (7 * t + 2.5);
	}

	float Easing::EaseInElastic(float t)
	{
		float t2 = t * t;
		return t2 * t2 * std::sin(t * std::numbers::pi * 4.5);
	}

	float Easing::EaseOutElastic(float t)
	{
		float t2 = (t - 1) * (t - 1);
		return 1 - t2 * t2 * std::cos(t * std::numbers::pi * 4.5);
	}

	float Easing::EaseInOutElastic(float t)
	{
		float t2;
		if( t < 0.45 )
		{
			t2 = t * t;
			return 8 * t2 * t2 * std::sin(t * std::numbers::pi * 9);
		}
		if( t < 0.55 )
		{
			return 0.5 + 0.75 * std::sin(t * std::numbers::pi * 4);
		}

		t2 = (t - 1) * (t - 1);
		return 1 - 8 * t2 * t2 * std::sin(t * std::numbers::pi * 9);
	}

	float Easing::EaseInBounce(float t)
	{
		return std::pow(2, 6 * (t - 1)) * std::abs(std::sin(t * std::numbers::pi * 3.5));
	}

	float Easing::EaseOutBounce(float t)
	{
		return 1 - std::pow(2, -6 * t) * std::abs(std::cos(t * std::numbers::pi * 3.5));
	}

	float Easing::EaseInOutBounce(float t)
	{
		if( t < 0.5 )
		{
			return 8 * std::pow(2, 8 * (t - 1)) * std::abs(std::sin( t * std::numbers::pi * 7));
		}

		return 1 - 8 * std::pow(2, -8 * t) * std::abs(std::sin( t * std::numbers::pi * 7));
	}
} // GEngine