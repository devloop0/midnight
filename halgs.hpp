#ifndef MIDNIGHT_HALGS_HPP
#define MIDNIGHT_HALGS_HPP

#include "core_types.hpp"
#include "algs.hpp"
#include "type_list.hpp"
#include "htype_list.hpp"
#include "placeholders.hpp"

using namespace midnight::core;
using namespace midnight::algs;
using namespace midnight::list;
using namespace midnight::hlist;
using namespace midnight::placeholders;

namespace midnight {
	namespace halgs {

		template<template<typename...> class F, typename... A> struct invoke_ {
			typedef typename F<A...>::type type;
		};

		template<template<typename...> class F> struct invoke_<F> {
			typedef typename F<>::type type;
		};

		template<class F, class T = nil_> struct sinvoke_ {
			typedef F type;
		};

		template<template<typename...> class F, class T, typename... A> struct __internal_apply {
			typedef typename conditional_<
				typename algs::list::is_end_<T>::bool_,
				invoke_<F, A...>,
				__internal_apply<F, typename T::rest, A..., typename T::current_type>
			>::type::type type;
		};

		template<template<typename...> class F, class T> struct apply_ {
			typedef typename __internal_apply<F, T>::type type;
		};

		template<template<typename...> class F> struct apply_<F, nil_> {
			typedef typename F<>::type type;
		};

		template<class F, class T = nil_> struct sapply_ {
			typedef F type;
		};

		template<class H, class X, typename... A> struct compose_ {
			typedef typename conditional_<
				typename algs::list::is_end_<H>::bool_,
				X,
				typename H::template current_type<
					typename compose_<
						typename H::rest,
						X
					>::type,
					A...
				>::type
			>::type type;
		};

		template<class X, typename... A> struct compose_<nil_, X, A...> {
			typedef X type;
		};

		template<class H, class A> struct __internal_demux {
			template<typename... V> using __created_Hct = typename H::template current_type<V...>;
			typedef typename conditional_<
				typename algs::list::is_end_<H>::bool_,
				A,
				type_list_<typename apply_<
					__created_Hct,
					typename __internal_demux<
						typename H::rest,
						A
					>::type
				>::type>
			>::type type;
		};

		template<class A> struct __internal_demux<nil_, A> {
			typedef A type;
		};

		template<class H, typename... A> struct demux_ {
			typedef typename __internal_demux<H, typename make_type_list_<A...>::type>::type::current_type type;
		};

		template<class H> struct demux_<H, nil_> {
			typedef typename H::current_type type;
		};

		template<class H> struct demux_<H> {
			typedef typename H::current_type type;
		};

		template<template<typename...> class A, template<typename...> class B> struct htypes_equal_ {
			typedef midnight::core::bool_<false> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<template<typename...> class A> struct htypes_equal_<A, A> {
			typedef midnight::core::bool_<true> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<typename... A> struct hidentity_ {
			typedef typename make_type_list_<A...>::type type;
		};

		template<> struct hidentity_<> {
			typedef nil_ type;
		};

		template<typename...> struct haccept_ : public accept_<void_> {

		};

		template<typename...> struct hreject_ : public reject_<void_> {

		};

		namespace hlist {
			
			template<class H, class I, template<typename...> class V> struct hinsert_ {
				template<typename... A> using __created_Hct = typename H::template current_type<A...>;
				typedef typename conditional_<
					typename logical_and_<
						typename algs::list::is_end_<H>::bool_,
						typename not_equals_<I, int_<0>>::bool_
					>::bool_,
					H,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						htype_list_<V, H>,
						htype_list_<
							__created_Hct,
							typename hinsert_<typename H::rest, sub_<I, int_<1>>, V>::type
						>
					>::type
				>::type type;
			};

			template<class I, template<typename...> class V> struct hinsert_<nil_, I, V> {
				typedef typename conditional_<
					typename equals_<I, int_<0>>::bool_,
					htype_list_<V>,
					nil_
				>::type type;
			};

			template<class H, template<typename...> class V> struct happend_ {
				typedef typename hinsert_<H, typename algs::list::len_<H>::length, V>::type type;
			};

			template<class H, class I> struct hat_ {
				template<typename... A> using type = typename conditional_<
					typename logical_or_<
						typename less_than_<I, int_<0>>::bool_,
						typename algs::list::is_end_<H>::bool_
					>::bool_,
					hat_<nil_, int_<0>>,
					hat_<typename H::rest, typename sub_<I, int_<1>>::int_>
				>::type::template type<A...>;
			};

			template<> struct hat_<nil_, int_<0>> {
				template<typename... A> using type = hnil_<A...>;
			};

			template<class H> struct hat_<H, int_<0>> {
				template<typename... A> using type = typename H::template current_type<A...>;
			};

			template<class I> struct hat_<nil_, I> {
				template<typename... A> using type = hnil_<A...>;
			};

			template<class H, class I = typename sub_<typename algs::list::len_<H>::length, int_<1>>::int_> struct hremove_ {
				template<typename... A> using __created_Hct = typename H::template current_type<A...>;
				typedef typename conditional_<
					typename algs::list::is_end_<H>::bool_,
					H,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						typename H::rest,
						htype_list_<
							__created_Hct,
							typename hremove_<typename H::rest, typename sub_<I, int_<1>>::int_>::type
						>
					>::type
				>::type type;
				template<typename... A> using removed_type = typename conditional_<
					typename algs::list::is_end_<H>::bool_,
					hremove_<nil_, int_<0>>,
					hremove_<typename H::rest, typename sub_<I, int_<1>>::int_>
				>::type::template removed_type<A...>;
			};

			template<class H> struct hremove_<H, int_<0>> {
				typedef typename H::rest type;
				template<typename... A> using removed_type = typename H::template current_type<A...>;
			};

			template<class I> struct hremove_<nil_, I> {
				typedef nil_ type;
				template<typename... A> using removed_type = hnil_<A...>;
			};

			template<> struct hremove_<nil_, int_<0>> {
				typedef nil_ type;
				template<typename... A> using removed_type = hnil_<A...>;
			};

			template<class H, class V, class I> struct __internal_hinsert_all_helper {
				template<typename... A> using __created_Vct = typename V::template current_type<A...>;
				typedef typename conditional_<
					typename algs::list::is_end_<V>::bool_,
					V,
					__internal_hinsert_all_helper<
						typename hinsert_<H, I, __created_Vct>::type,
						typename V::rest,
						typename add_<I, int_<1>>::int_
					>
				>::type::type type;
			};

			template<class H, class I> struct __internal_hinsert_all_helper<H, nil_, I> {
				typedef H type;
			};

			template<class H, class I, class V> struct hinsert_all_ {
				template<typename... A> using __created_Hct = typename H::template current_type<A...>;
				typedef typename conditional_<
					typename logical_and_<
						typename algs::list::is_end_<H>::bool_,
						typename not_equals_<I, int_<0>>::bool_
					>::bool_,
					H,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						__internal_hinsert_all_helper<H, V, int_<0>>,
						htype_list_<
							__created_Hct,
							typename hinsert_all_<typename H::rest, sub_<I, int_<1>>, V>::type
						>
					>::type::type
				>::type type;
			};

			template<class I, class V> struct hinsert_all_<nil_, I, V> {
				typedef typename conditional_<
					typename equals_<I, int_<0>>::bool_,
					V,
					nil_
				>::type type;
			};
			
			template<class H, class V> struct happend_all_ {
				typedef typename hinsert_all_<H, typename algs::list::len_<H>::length, V>::type type;
			};

			template<template<typename...> class A, class H, class I, class N> struct __internal_hfill {
				typedef typename fail_<
					typename less_than_<N, int_<0>>::bool_
				>::type __internal_hfill_sanity_check;
				typedef typename conditional_<
					typename greater_than_or_equal_to_<I, N>::bool_,
					H,
					__internal_hfill<A, htype_list_<A, H>, add_<I, int_<1>>, N>
				>::type::type type;
			};

			template<template<typename...> class V, class N> struct hfill_ {
				typedef typename __internal_hfill<V, nil_, int_<0>, N>::type type;
			};

			template<class A> struct is_htype_list_ {
				typedef midnight::core::bool_<false> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<template<typename...> class A, class B> struct is_htype_list_<htype_list_<A, B>> {
				typedef midnight::core::bool_<true> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class H, class N = int_<1>> struct hadvance_ {
				typedef typename fail_<
					typename not_<typename is_htype_list_<H>::bool_>::bool_
				>::type __hadvance_sanity_check;
				typedef typename conditional_<
					typename logical_or_<
						typename algs::list::is_end_<H>::bool_,
						equals_<N, int_<0>>
					>::bool_,
					H,
					hadvance_<typename H::rest, sub_<N, int_<1>>>
				>::type::type type;
			};
		}

		template<class H, class T> struct __internal_list_lockstep_helper {
			typedef typename fail_<
				typename not_equals_<
					typename algs::list::len_<H>::length,
					typename algs::list::len_<T>::length
				>::bool_
			>::type __internal_list_lockstep_helper_sanity_check;
			template<typename... A> using __created_Hct = typename H::template current_type<A...>;
			typedef typename conditional_<
				typename logical_or_<
					typename algs::list::is_end_<H>,
					typename algs::list::is_end_<T>
				>::bool_,
				nil_,
				type_list_<
					typename __created_Hct<typename T::current_type>::type,
					typename __internal_list_lockstep_helper<
						typename H::rest,
						typename T::rest
					>::type
				>
			>::type type;
		};

		template<> struct __internal_list_lockstep_helper<nil_, nil_> {
			typedef nil_ type;
		};

		template<template<typename...> class F, class H, class T> struct list_lockstep_ {
			typedef typename fail_<
				typename not_equals_<
					typename algs::list::len_<H>::length,
					typename algs::list::len_<T>::length
				>::bool_
			>::type __internal_lockstep_sanity_check;
			typedef typename __internal_list_lockstep_helper<H, T>::type __internal_mapped;
			typedef typename apply_<F, __internal_mapped>::type type;
		};

		template<class F, class H = nil_, class T = nil_> struct slist_lockstep_ {
			typedef F type;
		};

		template<template<typename...> class F, class H, typename... B> struct __internal_lockstep_helper {
			typedef typename make_type_list_<B...>::type __internal_a_list;
			typedef typename list_lockstep_<F, H, __internal_a_list>::type type;
		};

		template<template<typename...> class F, template<typename...> class... A> struct lockstep_ {
			typedef typename make_htype_list_<A...>::type __internal_ho_list;
			template<typename... B> using type = __internal_lockstep_helper<F, __internal_ho_list, B...>;
		};

		template<class F, class A, class B = nil_> struct __internal_slockstep_helper {
			typedef typename slist_lockstep_<F, A, B>::type type;
		};

		template<class F, class A = nil_> struct slockstep_ {
			template<class B = nil_> using type = __internal_slockstep_helper<F, A, B>;
		};

		template<template<typename...> class F, class N, typename... A> struct __internal_quote_helper_variadic {
			typedef int_<sizeof...(A)> __internal_parm_pack_len;
			typedef typename fail_<
				typename not_<
					logical_or_<
						less_than_<N, int_<0>>,
						equals_<N, __internal_parm_pack_len>
					>
				>::bool_
			>::type __internal_quote_helper_variadic_sanity_check;
			typedef typename invoke_<F, A...>::type type;
		};

		template<template<typename...> class F, class N, class A> struct __internal_quote_helper_list {
			typedef typename algs::list::len_<A>::length __internal_args_len;
			typedef typename fail_<
				typename not_<
					logical_or_<
						less_than_<N, int_<0>>,
						equals_<N, __internal_args_len>
					>
				>::bool_
			>::type __internal_quote_helper_list_sanity_check;
			typedef typename apply_<F, A>::type type;
		};

		template<template<typename...> class F, class N = int_<-1>> struct quote_ {
			template<typename... A> using call = __internal_quote_helper_variadic<F, N, A...>;
			template<typename A> using call_list = __internal_quote_helper_list<F, N, A>;
		};

		template<template<typename...> class F, typename... A> struct __internal_partial_helper {
			typedef typename invoke_<F, A...>::type type;
			typedef int_<sizeof...(A)> total_args;
		};

		template<template<typename...> class F, typename... A> struct partial_ {
			template<typename... B> using delay = partial_<F, A..., B...>;
			typedef __internal_partial_helper<F, A...> accumulate;
		};

		template<class P, class A, class O> struct __internal_bind_replace_placeholders {
			typedef typename fail_<
				typename not_equals_<
					typename algs::list::len_<P>::length,
					typename algs::list::len_<A>::length
				>::bool_
			>::type __internal_bind_replace_placeholders_sanity_check;
			typedef typename conditional_<
				typename logical_or_<
					typename algs::list::is_end_<P>::bool_,
					typename algs::list::is_end_<A>::bool_
				>::bool_,
				O,
				__internal_bind_replace_placeholders<
					typename P::rest, typename A::rest, typename algs::list::replace_all_<O, typename P::current_type, typename A::current_type>::type
				>
			>::type::type type;
		};

		template<class O> struct __internal_bind_replace_placeholders<nil_, nil_, O> {
			typedef O type;
		};

		template<template<typename...> class F, class P, class O, typename... A> struct __internal_bind_call_helper {
			typedef typename make_type_list_<A...>::type __placeheld_arg_list;
			typedef typename fail_<
				typename not_equals_<
					typename algs::list::len_<P>::length,
					typename algs::list::len_<__placeheld_arg_list>::length
				>::bool_
			>::type __internal_bind_call_helper_sanity_check;
			typedef typename __internal_bind_replace_placeholders<P, __placeheld_arg_list, O>::type __actual_args;
			typedef typename apply_<F, __actual_args>::type type;
		};

		template<template<typename...> class F, class P, class O, class N> struct __internal_bind_create_proper_template_bindings {

		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<0>> {
			template<typename...> using type = __internal_bind_call_helper<F, P, O>;
			typedef typename midnight::core::int_<0> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<1>> {
			template<typename A1> using type = __internal_bind_call_helper<F, P, O, A1>;
			typedef typename midnight::core::int_<1> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<2>> {
			template<typename A1, typename A2> using type = __internal_bind_call_helper<F, P, O, A1, A2>;
			typedef typename midnight::core::int_<2> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<3>> {
			template<typename A1, typename A2, typename A3> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3>;
			typedef typename midnight::core::int_<3> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<4>> {
			template<typename A1, typename A2, typename A3, typename A4> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4>;
			typedef typename midnight::core::int_<4> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<5>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5>;
			typedef typename midnight::core::int_<5> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<6>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6>;
			typedef typename midnight::core::int_<6> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<7>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7>;
			typedef typename midnight::core::int_<7> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<8>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8>;
			typedef typename midnight::core::int_<8> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<9>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9>;
			typedef typename midnight::core::int_<9> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<10>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>;
			typedef typename midnight::core::int_<10> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<11>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>;
			typedef typename midnight::core::int_<11> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<12>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>;
			typedef typename midnight::core::int_<12> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<13>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
				typename A13> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13>;
			typedef typename midnight::core::int_<13> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<14>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
				typename A13, typename A14> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14>;
			typedef typename midnight::core::int_<14> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<15>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
				typename A13, typename A14, typename A15> using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15>;
			typedef typename midnight::core::int_<15> expected_args;
		};

		template<template<typename...> class F, class P, class O> struct __internal_bind_create_proper_template_bindings<F, P, O, int_<16>> {
			template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12,
				typename A13, typename A14, typename A15, typename A16>
				using type = __internal_bind_call_helper<F, P, O, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16>;
			typedef typename midnight::core::int_<16> expected_args;
		};

		template<template<typename...> class F, typename... A> struct bind_ {
			typedef typename make_type_list_<A...>::type __args_list;
			typedef typename algs::list::filter_<__args_list, is_placeholder_>::type __filtered_args;
			typedef typename algs::list::unique_<typename algs::list::sort_<__filtered_args>::type>::type __sorted_placeholders;
			typedef typename algs::list::len_<__sorted_placeholders>::length __proper_specialization;
			typedef __internal_bind_create_proper_template_bindings<F, __sorted_placeholders, __args_list, __proper_specialization> bind;
		};

		template<template<typename...> class F, template<typename> class G, typename... A> struct on_ {
			typedef typename make_type_list_<A...>::type __arg_list;
			typedef typename algs::list::map_<__arg_list, G>::type __mapped_arg_list;
			typedef typename apply_<F, __mapped_arg_list>::type type;
		};

		template<template<typename> class F, class N, class X> struct iterate_ {
			typedef typename fail_<
				typename less_than_<X, int_<0>>::bool_
			>::type __internal_iterate_sanity_check;
			typedef typename conditional_<
				typename equals_<N, int_<0>>::bool_,
				X,
				iterate_<F, sub_<N, int_<1>>, typename F<X>::type>
			>::type::type type;
		};

		template<template<typename> class F, class N> struct iterate_fn_ {
			template<class X> using type = iterate_<F, N, X>;
		};
	}
}

#endif
