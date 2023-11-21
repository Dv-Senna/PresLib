#pragma once



namespace pl::utils
{
	template <typename T>
	T square(const T &value);
	template <typename T>
	T cube(const T &value);

	template <typename T>
	T linear(float t, const T &p0, const T &p1);
	template <typename T>
	T quadraticBezier(float t, const T &p0, const T &p1, const T &p2);
	template <typename T>
	T cubicBezier(float t, const T &p0, const T &p1, const T &p2, const T &p3);

} // namespace pl::utils


#include "function.inl"