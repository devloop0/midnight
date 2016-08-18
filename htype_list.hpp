#ifndef MIDNIGHT_HTYPE_LIST_HPP
#define MIDNIGHT_HTYPE_LIST_HPP

#include "type_list.hpp"
#include "core_types.hpp"

using namespace midnight::list;
using namespace midnight::core;

namespace midnight {
	namespace hlist {

		template<typename... A> struct hnil_ {
			typedef void_ current_type, rest;
			typedef hnil_<A...> type;
			static constexpr decltype(nullptr) value = nullptr;
		};

		template<template<typename...> class F, class R = nil_> struct htype_list_ {
			template<typename... A> using current_type = F<A...>;
			typedef R rest;
			typedef htype_list_<F, R> type;
		};

		template<template<typename...> class...> struct make_htype_list_ {
		
		};

		template<template<typename...> class F, template<typename...> class... R> struct make_htype_list_<F, R...> {
			typedef htype_list_<F , typename make_htype_list_<R...>::type> type;
		};

		template<template<typename...> class F> struct make_htype_list_<F> {
			typedef htype_list_<F> type;
		};

		template<> struct make_htype_list_<> {
			typedef nil_ type;
		};
	}
}

#endif
