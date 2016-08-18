#ifndef MIDNIGHT_VARIADIC_BOOL_OPERATORS_HPP
#define MIDNIGHT_VARIADIC_BOOL_OPERATORS_HPP

#include "core_types.hpp"
#include "type_list.hpp"
#include "bool_operators.hpp"
#include "algs.hpp"

using namespace midnight::core;
using namespace midnight::list;
using namespace midnight::operators;
using namespace midnight::algs;

namespace midnight {
	namespace voperators {

		template<class F, class S, typename... R> struct vlogical_or_ {
			typedef typename conditional_<
				typename logical_or_<F, S>::bool_,
				midnight::core::bool_<true>,
				vlogical_or_<midnight::core::bool_<false>, R...>
			>::type::type type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vlogical_or_<F, S> {
			typedef typename logical_or_<F, S>::bool_ type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vlogical_and_ {
			typedef typename conditional_<
				typename not_<typename logical_and_<F, S>::bool_>::bool_,
				midnight::core::bool_<false>,
				vlogical_and_<midnight::core::bool_<true>, R...>
			>::type::type type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vlogical_and_<F, S> {
			typedef typename logical_and_<F, S>::bool_ type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};
	}
}

#endif
