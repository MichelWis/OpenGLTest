#pragma once
#include <stdio.h>
#include <math.h>
#include <array>
#include "../Logging/Log.h"

constexpr auto FLOATING_POINT_EPSILON = .0000001;

namespace Tools {
	template<int n, typename T>
	std::array<T, n> InitializerListToArray(std::initializer_list<T>& _il) {
		std::array<T, n> arr;
		int i = 0;
		for (auto e : _il) {
			arr[i] = e;
			i++;
		}
		return arr;
	}

	template<typename T>
	inline bool Equals(const T& _a, const T& _b) {
		return fabs(_a - _b) < FLOATING_POINT_EPSILON;
	}
	inline bool Equals(const int& _a, const int& _b) {
		return _a == _b;
	}
}