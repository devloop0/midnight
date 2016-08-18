#ifndef MIDNIGHT_NUMERIC_OPERATORS_HPP
#define MIDNIGHT_NUMERIC_OPERATORS_HPP

#include "core_types.hpp"

using midnight::core::int_;

namespace midnight {
	namespace operators {

		template<class T, class U> struct add_ {
			typedef decltype(T{} + U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr add_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct sub_ {
			typedef decltype(T{} - U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr sub_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct times_ {
			typedef decltype(T{} * U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr times_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct divide_ {
			typedef decltype(T{} / U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr divide_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct mod_ {
			typedef decltype(T{} % U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr mod_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct bitwise_and_ {
			typedef decltype(T{} & U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr bitwise_and_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct bitwise_or_ {
			typedef decltype(T{} | U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr bitwise_or_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct bitwise_xor_ {
			typedef decltype(T{} ^ U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr bitwise_xor_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct shift_left_ {
			typedef decltype(T{} << U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr shift_left_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T, class U> struct shift_right_ {
			typedef decltype(T{} >> U{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr shift_right_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T> struct plus_ {
			typedef decltype(+T{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr plus_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T> struct minus_ { 
			typedef decltype(-T{}) type;
			static constexpr decltype(type::value) value = type::value;
			constexpr minus_() {}
			typedef midnight::core::int_<value> int_;
		};

		template<class T> struct complement_ {
			typedef decltype(~T{}) type;	
			static constexpr decltype(type::value) value = type::value;
			constexpr complement_() {}
			typedef midnight::core::int_<value> int_;
		};
	}
}

#endif
