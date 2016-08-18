#ifndef MIDNIGHT_CONDITIONAL_OPERATORS_HPP
#define MIDNIGHT_CONDITIONAL_OPERATORS_HPP

#include "core_types.hpp"
#include "type_list.hpp"

using midnight::core::bool_;

namespace midnight {
	namespace operators {

		template<class C, class T, class F> struct conditional_ {};

		template<class T, class F> struct conditional_<bool_<true>, T, F> {
			typedef T type;
		};

		template<class T, class F> struct conditional_<bool_<false>, T, F> {
			typedef F type;
		};
	}
}

#endif
