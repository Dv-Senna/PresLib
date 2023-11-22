#include "function.hpp"



namespace pl::utils
{
	template <typename T>
	T square(const T &value)
	{
		return value * value;
	}



	template <typename T>
	T cube(const T &value)
	{
		return value * value * value;
	}



	template <typename T>
	T linear(float t, const T &p0, const T &p1)
	{
		return (p1 - p0) * t + p0;
	}



	template <typename T>
	T quadraticBezier(float t, const T &p0, const T &p1, const T &p2)
	{
		return pl::utils::square(1.f - t) * p0 + 2.f * (1.f - t) * t * p1 + t*t * p2;
	}



	template <typename T>
	T cubicBezier(float t, const T &p0, const T &p1, const T &p2, const T &p3)
	{
		return pl::utils::cube(1.f - t) * p0 + 3 * pl::utils::square(1.f - t) * t * p1 + 3 * (1.f - t) * t*t * p2 + t*t*t * p3;
	}



} // namespace pl::utils
