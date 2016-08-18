#ifndef MIDNIGHT_TYPE_LIST_HPP
#define MIDNIGHT_TYPE_LIST_HPP

#include "core_types.hpp"

using midnight::core::void_;

namespace midnight {
	namespace list {

		struct nil_ {
			typedef void_ current_type, rest;
			static constexpr decltype(nullptr) value = nullptr;
			typedef nil_ type;
		};
		
		template<class F, class R = nil_> struct type_list_ {
			typedef F current_type;
			typedef R rest;
			typedef type_list_<F, R> type;
		};

		template<typename...> struct make_type_list_ {
		
		};

		template<class F, class... R> struct make_type_list_<F, R...> {
			typedef type_list_<F, typename make_type_list_<R...>::type> type;
		};

		template<class F> struct make_type_list_<F> {
			typedef type_list_<F> type;
		};

		template<> struct make_type_list_<> {
			typedef nil_ type;
		};
	}
}

#endif
