#ifndef MIDNIGHT_GENERIC_NUMERIC_OPERATORS_HPP
#define MIDNIGHT_GENERIC_NUMERIC_OPERATORS_HPP

#include "core_types.hpp"

using midnight::core::int_;
using midnight::core::bool_;

namespace midnight {
	namespace core {

		template<class T, class V> constexpr int_<(int) T::value + (int) V::value> operator+(T, V) { return int_<(int) T::value + (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value - (int) V::value> operator-(T, V) { return int_<(int) T::value - (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value * (int) V::value> operator*(T, V) { return int_<(int) T::value * (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value / (int) V::value> operator/(T, V) { return int_<(int) T::value / (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value % (int) V::value> operator%(T, V) { return int_<(int) T::value % (int) V::value>{}; }

		template<class T, class V> constexpr int_<(int) T::value & (int) V::value> operator&(T, V) { return int_<(int) T::value & (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value | (int) V::value> operator|(T, V) { return int_<(int) T::value | (int) V::value>{}; }
		template<class T, class V> constexpr int_<(int) T::value ^ (int) V::value> operator^(T, V) { return int_<(int) T::value ^ (int) V::value>{}; }
		template<class T, class V> constexpr int_<((int) T::value << (int) V::value)> operator<<(T, V) { return int_<((int) T::value << (int) V::value)>{}; }
		template<class T, class V> constexpr int_<((int) T::value >> (int) V::value)> operator>>(T, V) { return int_<((int) T::value >> (int) V::value)>{}; }

		template<class T> constexpr int_<+ ((int) T::value)> operator+(T) { return int_<+ ((int) T::value)>{}; }
		template<class T> constexpr int_<- ((int) T::value)> operator-(T) { return int_<- ((int) T::value)>{}; }
		template<class T> constexpr int_<~ ((int) T::value)> operator~(T) { return int_<~ ((int) T::value)>{}; }

		template<class T, class V> constexpr bool_<(T::value > V::value)> operator>(T, V) { return bool_<(T::value > V::value)>{}; }
		template<class T, class V> constexpr bool_<(T::value < V::value)> operator<(T, V) { return bool_<(T::value < V::value)>{}; }
		template<class T, class V> constexpr bool_<(T::value <= V::value)> operator<=(T, V) { return bool_<(T::value <= V::value)>{}; }
		template<class T, class V> constexpr bool_<(T::value >= V::value)> operator>=(T, V) { return bool_<(T::value >= V::value)>{}; }
		template<class T, class V> constexpr bool_<T::value == V::value> operator==(T, V) { return bool_<T::value == V::value>{}; }
		template<class T, class V> constexpr bool_<T::value != V::value> operator!=(T, V) { return bool_<T::value != V::value>{}; }

		template<class T, class V> constexpr bool_<T::value && V::value> operator&&(T, V) { return bool_<T::value && V::value>{}; }
		template<class T, class V> constexpr bool_<T::value || V::value> operator||(T, V) { return bool_<T::value || V::value>{}; }

		template<class T> constexpr bool_<!T::value> operator!(T) { return bool_<!T::value>{}; }
	}
}

#endif
