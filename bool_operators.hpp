#ifndef MIDNIGHT_BOOL_OPERATORS_HPP
#define MIDNIGHT_BOOL_OPERATORS_HPP

#include "core_types.hpp"

using midnight::core::int_;
using midnight::core::bool_;

namespace midnight {
	namespace operators {

		template<class T, class U> struct equals_ {
			typedef decltype(T{} == U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr equals_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct not_equals_ {
			typedef decltype(T{} != U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr not_equals_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct greater_than_ {
			typedef decltype(T{} > U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr greater_than_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct less_than_ {
			typedef decltype(T{} < U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr less_than_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct greater_than_or_equal_to_ {
			typedef decltype(T{} >= U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr greater_than_or_equal_to_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct less_than_or_equal_to_ {
			typedef decltype(T{} <= U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr less_than_or_equal_to_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct logical_and_ {
			typedef decltype(T{} && U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr logical_and_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T, class U> struct logical_or_ {
			typedef decltype(T{} || U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr logical_or_() {}
			typedef midnight::core::bool_<value> bool_;
		};

		template<class T> struct not_ {
			typedef decltype(!T{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr not_() {}
			typedef midnight::core::bool_<value> bool_;
		};
	}
}

#endif
