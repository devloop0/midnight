#ifndef MIDNIGHT_ALGS_HPP
#define MIDNIGHT_ALGS_HPP

#include "core_types.hpp"
#include "generic_operators.hpp"
#include "conditional_operator.hpp"
#include "type_list.hpp"
#include "numeric_operators.hpp"
#include "bool_operators.hpp"

using midnight::core::int_;
using midnight::core::bool_;
using namespace midnight::operators;
using midnight::list::type_list_;
using midnight::list::nil_;
using midnight::core::void_;
using midnight::core::char_;
using midnight::core::long_;
using midnight::core::size_t_;

namespace midnight {
	namespace algs {

		template<class T, class V> struct types_equal_ {
			typedef midnight::core::bool_<false> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct types_equal_<T, T> {
			typedef midnight::core::bool_<true> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_int_ {
			typedef typename midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<int N> struct is_int_<int_<N>> {
			typedef typename midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_bool_ {
			typedef typename midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<bool B> struct is_bool_<bool_<B>> {
			typedef typename midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_long_ {
			typedef typename midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};
	
		template<long L> struct is_long_<long_<L>> {
			typedef typename midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_size_t_ {
			typedef typename midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<unsigned int S> struct is_size_t_<size_t_<S>> {
			typedef typename midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_char_ {
			typedef typename midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<char C> struct is_char_<char_<C>> {
			typedef typename midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct is_void_ {
			typedef typename types_equal_<T, void_>::bool_ bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct truthy_ {
			typedef midnight::core::bool_<(bool) T::value> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<int N> struct truthy_<int_<N>> {
			typedef midnight::core::bool_<(N > 0)> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<bool B> struct truthy_<bool_<B>> {
			typedef midnight::core::bool_<B> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<> struct truthy_<void_> {
			typedef midnight::core::bool_<false> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<> struct truthy_<nil_> {
			typedef midnight::core::bool_<false> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<typename F, typename... R> struct truthy_<type_list_<F, R...>> {
			typedef midnight::core::bool_<true> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<char C> struct truthy_<char_<C>> {
			typedef midnight::core::bool_<(C > 0)> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};
		
		template<long L> struct truthy_<long_<L>> {
			typedef midnight::core::bool_<(L > 0)> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<unsigned int S> struct truthy_<size_t_<S>> {
			typedef midnight::core::bool_<(S != 0)> type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class B> struct fail_ {

		};

		template<> struct fail_<bool_<false>> {
			typedef void_ type;
		};

		template<class T> struct identity_ {
			typedef T type;
		};

		template<class T> struct accept_ {
			typedef midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T> struct reject_ {
			typedef midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		namespace list {

			template<class A> struct is_type_list_ {
				typedef midnight::core::bool_<false> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class A, class B> struct is_type_list_<type_list_<A, B>> {
				typedef midnight::core::bool_<true> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<> struct is_type_list_<nil_> {
				typedef midnight::core::bool_<true> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T> struct is_nil_ {
				typedef typename types_equal_<T, nil_>::bool_ bool_, type;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T> struct is_end_ {
				typedef typename is_nil_<T>::bool_ bool_, type;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T> struct is_empty_ {
				typedef typename is_nil_<T>::bool_ bool_, type;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class S> struct __internal_len {
				typedef conditional_<
					typename is_end_<T>::bool_,
					S,
					__internal_len<typename T::rest, add_<S, midnight::core::int_<1>>>
				> res;
				typedef typename res::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::int_<value> int_, length;
			};
			
			template<class T> struct len_ {
				typedef typename __internal_len<T, midnight::core::int_<0>>::type __internal_type;
				static constexpr decltype(__internal_type::value) value = __internal_type::value;
				typedef midnight::core::int_<value> int_, length, type;
			};

			template<class T> struct car_ {
				typedef typename T::type type;
			};

			template<class T> struct cdr_ {
				typedef typename T::rest type;
			};

			template<class T, class N> struct at_ {
				typedef typename conditional_<
						typename logical_or_<
							typename less_than_<N, int_<0>>::bool_,
							typename is_end_<T>::bool_
						>::bool_,
						nil_,
						typename conditional_<
							typename equals_<N, int_<0>>::bool_,
							typename T::current_type,
							at_<typename T::rest, sub_<N, int_<1>>>
						>::type
					>::type::type type;
			};

			template<class N> struct at_<nil_, N> {
				typedef nil_ type;
			};

			template<class T, template<typename> class P> struct any_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::bool_<false>,
					typename conditional_<
						typename P<typename T::current_type>::type,
						midnight::core::bool_<true>,
						any_<typename T::rest, P>
					>::type
				>::type::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::bool_<value> bool_;
			};

			template<template<typename> class P> struct any_<nil_, P> {
				typedef midnight::core::bool_<false> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, template<typename> class P> struct all_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::bool_<true>,
					typename conditional_<
						typename not_<typename P<typename T::current_type>::type>::bool_,
						midnight::core::bool_<false>,
						all_<typename T::rest, P>
					>::type
				>::type::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::bool_<value> bool_;
			};

			template<template<typename> class P> struct all_<nil_, P> {
				typedef typename midnight::core::bool_<true> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class I, class V> struct insert_ {
				typedef typename conditional_<
					typename logical_and_<
						typename is_end_<T>::bool_,
						typename not_equals_<I, int_<0>>::bool_
					>::bool_,
					T,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						type_list_<V, T>,
						type_list_<
							typename T::current_type, 
							typename insert_<typename T::rest, sub_<I, int_<1>>, V>::type
						>
					>::type
				>::type type;
			};

			template<class I, class V> struct insert_<nil_, I, V> {
				typedef typename conditional_<
					typename equals_<I, int_<0>>::bool_,
					type_list_<V>,
					nil_
				>::type type;
			};

			template<class T, class V> struct append_ {
				typedef typename insert_<T, typename len_<T>::length, V>::type type;
			};

			template<class T, class V, class I> struct __internal_insert_all_helper {
				typedef typename conditional_<
					typename is_end_<V>::bool_,
					T,
					__internal_insert_all_helper<
						typename insert_<T, I, typename V::current_type>::type,
						typename V::rest,
						typename add_<I, int_<1>>::int_
					>
				>::type::type type;
			};

			template<class T, class I> struct __internal_insert_all_helper<T, nil_, I> {
				typedef T type;
			};

			template<class T, class I, class V> struct insert_all_ {
				typedef typename conditional_<
					typename logical_and_<
						typename is_end_<T>::bool_,
						typename not_equals_<I, int_<0>>::bool_
					>::bool_,
					T,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						__internal_insert_all_helper<T, V, int_<0>>,
						type_list_<
							typename T::current_type,
							typename insert_all_<typename T::rest, sub_<I, int_<1>>, V>::type
						>
					>::type::type
				>::type type;
			};

			template<class I, class V> struct insert_all_<nil_, I, V> {
				typedef typename conditional_<
					typename equals_<I, int_<0>>::bool_,
					V,
					nil_
				>::type type;
			};

			template<class T, class V> struct append_all_ {
				typedef typename insert_all_<T, typename len_<T>::length, V>::type type;
			};

			template<class T, class I = sub_<typename len_<T>::length, int_<1>>> struct remove_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					T,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						typename T::rest,
						type_list_<
							typename T::current_type,
							typename remove_<typename T::rest, sub_<I, int_<1>>>::type
						>
					>::type
				>::type type;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					T,
					typename conditional_<
						typename equals_<I, int_<0>>::bool_,
						typename T::current_type,
						typename remove_<typename T::rest, sub_<I, int_<1>>>::removed_type
					>::type
				>::type removed_type;
			};

			template<class I> struct remove_<nil_, I> {
				typedef nil_ type, removed_type;
			};

			template<class T, class V, class I, template<typename, typename> class C> struct __internal_index_of {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::int_<-1>,
					typename conditional_<
						typename C<typename T::current_type, V>::type,
						I,
						__internal_index_of<typename T::rest, V, add_<I, midnight::core::int_<1>>, C>
					>::type
				>::type::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::int_<value> int_;
			};

			template<class V, class I, template<typename, typename> class C> struct __internal_index_of<nil_, V, I, C> {
				typedef typename midnight::core::int_<-1> type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class V, template<typename, typename> class C = types_equal_> struct index_of_ {
				typedef typename __internal_index_of<T, V, midnight::core::int_<0>, C>::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::int_<value> int_;
			};

			template<class T, class V, class R, template<typename, typename> class C> struct __internal_index_of_all {
				typedef typename fail_<
					typename not_<typename is_type_list_<V>::bool_>::bool_
				>::type __internal_index_of_all_sanity_check;
				typedef typename conditional_<
					typename is_end_<V>::bool_,
					R,
					__internal_index_of_all<
						T,
						typename V::rest,
						typename append_<R, typename index_of_<T, typename V::current_type, C>::type>::type,
						C
					>
				>::type::type type;
			};

			template<class T, class R, template<typename, typename> class C> struct __internal_index_of_all<T, nil_, R, C> {
				typedef R type;
			};

			template<class T, class V, template<typename, typename> class C = types_equal_> struct index_of_all_ {
				typedef typename __internal_index_of_all<T, V, nil_, C>::type type;
			};
			
			template<class T, template<typename> class P> struct none_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::bool_<true>,
					typename conditional_<
						typename P<typename T::current_type>::type,
						midnight::core::bool_<false>,
						none_<typename T::rest, P>
					>::type
				>::type::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::bool_<value> bool_;
			};

			template<template<typename> class P> struct none_<nil_, P> {
				typedef midnight::core::bool_<true> type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};
	
			template<class T, class V, template<typename, typename> class C = types_equal_> struct remove_type_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					T,
					typename conditional_<
						typename C<typename T::current_type, V>::type,
						typename T::rest,
						type_list_<
							typename T::current_type,
							typename remove_type_<typename T::rest, V>::type
						>
					>::type
				>::type type;
				typedef typename index_of_<T, V, C>::int_ removed_index;
			};

			template<class V, template<typename, typename> class C> struct remove_type_<nil_, V, C> {
				typedef nil_ type;
				typedef int_<-1> removed_index;
			};

			template<class T, template<typename> class P, template<typename> class C, class I, class E> struct __internal_map {
				typedef typename conditional_<
					typename logical_or_<
						typename is_end_<T>::bool_,
						typename greater_than_or_equal_to_<I ,E>::bool_
					>::bool_,
					T,
					type_list_<
						typename conditional_<
							typename C<typename T::current_type>::type,
							typename P<typename T::current_type>::type,
							typename T::current_type
						>::type,
						typename __internal_map<typename T::rest, P, C, add_<I, int_<1>>, E>::type
					>
				>::type type;
			};

			template<template<typename> class P, template<typename> class C, class I, class E>
				struct __internal_map<nil_, P, C, I, E> {
				typedef nil_ type;
			};

			template<class T, template<typename> class P, template<typename> class C = accept_, 
				class N = typename len_<T>::length> struct map_ {
				typedef typename __internal_map<T, P, C, int_<0>, N>::type type;
			};

			template<class T, template<typename> class P, class I, class E> struct __internal_filter {
				typedef typename conditional_<
					typename logical_or_<
						typename is_end_<T>::bool_,
						typename greater_than_or_equal_to_<I, E>::bool_
					>::bool_,
					T,
					typename conditional_<
						typename P<typename T::current_type>::type,
						type_list_<
							typename T::current_type,
							typename __internal_filter<typename T::rest, P, add_<I, int_<1>>, E>::type
						>,
						typename __internal_filter<typename T::rest, P, add_<I, int_<1>>, E>::type
					>::type
				>::type type;
			};

			template<template<typename> class P, class I, class E> struct __internal_filter<nil_, P, I, E> {
				typedef nil_ type;
			};

			template<class T, template<typename> class P, class N = typename len_<T>::length> struct filter_ {
				typedef typename __internal_filter<T, P, int_<0>, N>::type type;
			};

			template<class B, class T, template<typename, typename> class R, template<typename> class A = identity_> struct reduce_right_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					B,
					typename reduce_right_<
						typename A<typename R<B, typename T::current_type>::type>::type,
						typename T::rest,
						R>::type
				>::type type;
			};

			template<class B, template<typename, typename> class R, template<typename> class A> struct reduce_right_<B, nil_, R, A> {
				typedef B type;
			};

			template<class B, class T, template<typename, typename> class R, template<typename> class A = identity_> struct reduce_left_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					B,
					typename A<typename R<
						typename T::current_type,
						typename reduce_left_<
							B,
							typename T::rest,
							R
						>::type
					>::type>::type
				>::type type;
			};

			template<class B, template<typename, typename> class R, template<typename> class A> struct reduce_left_<B, nil_, R, A> {
				typedef B type;
			};

			template<class T, class V, class I, class N> struct __internal_fill {
				typedef typename fail_<typename less_than_<N, int_<0>>::bool_>::type __internal_size_check;
				typedef typename conditional_<
					typename greater_than_or_equal_to_<I, N>::bool_,
					T,
					__internal_fill<type_list_<V, T>, V, add_<I, int_<1>>, N>
				>::type::type type;
			};

			template<class V, class N> struct fill_ {
				typedef typename __internal_fill<nil_, V, int_<0>, N>::type type;
			};

			template<class T, class I, class E, class S> struct __internal_range {
				typedef typename fail_<
					typename logical_or_<
						typename less_than_<I, int_<0>>::bool_,
						typename logical_or_<
							typename less_than_<E, int_<0>>::bool_,
							typename less_than_or_equal_to_<S, int_<0>>::bool_
						>::bool_
					>::bool_
				>::type __internal_range_sanity_check;
				typedef typename conditional_<
					typename greater_than_or_equal_to_<I, E>::bool_,
					T,
					__internal_range<typename append_<T, I>::type, typename add_<I, S>::int_, E, S>
				>::type::type type;
			};

			template<class I, class E, class S = int_<1>> struct range_ {
				typedef typename __internal_range<nil_, I, E, S>::type type;
			};

			template<class E> struct srange_ : public range_<int_<0>, E, int_<1>> {

			};

			template<class S, class I, class T, template<typename> class P> struct __internal_where {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					S,
					typename conditional_<
						typename P<typename T::current_type>::type,
						__internal_where<typename append_<S, I>::type, typename add_<I, int_<1>>::int_, typename T::rest, P>,
						__internal_where<S, typename add_<I, int_<1>>::int_, typename T::rest, P>
					>::type
				>::type::type type;
			};

			template<class S, class I, template<typename> class P> struct __internal_where<S, I, nil_, P> {
				typedef S type;
			};

			template<class T, template<typename> class P> struct where_ {
				typedef typename __internal_where<nil_, int_<0>, T, P>::type type;
			};

			template<class C, class T, class S> struct __internal_from {
				typedef typename fail_<
					typename logical_or_<
						typename greater_than_or_equal_to_<typename S::current_type, typename len_<T>::length>::bool_,
						typename less_than_<typename S::current_type, int_<0>>::bool_
					>::bool_
				>::type __internal_from_sanity_check;
				typedef typename conditional_<
					typename is_end_<S>::bool_,
					C,
					__internal_from<
						typename append_<C, typename at_<T, typename S::current_type>::type>::type,
						T,
						typename S::rest
					>
				>::type::type type;
			};

			template<class C, class T> struct __internal_from<C, T, nil_> {
				typedef C type;
			};

			template<class T, class S> struct from_ {
				typedef typename __internal_from<nil_, T, S>::type type;
			};

			template<class T, class I, class E, class S = int_<1>> struct slice_ {
				typedef typename from_<T, typename range_<I, E, S>::type>::type type;
			};

			template<class T, class E> struct sslice_ : public slice_<T, int_<0>, E, int_<1>> {

			};

			template<class T> struct is_int_list_ : public all_<T, is_int_> {

			};

			template<class I, class T, template<typename, typename> class C> struct __internal_is_sorted {
				typedef typename conditional_<
					typename not_<typename C<I, typename T::current_type>::type>::bool_,
					bool_<false>,
					typename __internal_is_sorted<typename T::current_type, typename T::rest, C>::type
				>::type::type type;
			};

			template<class I, template<typename, typename> class C> struct __internal_is_sorted<I, nil_, C> {
				typedef bool_<true> type;
			};

			template<class T, template<typename, typename> class C = less_than_or_equal_to_> struct is_sorted_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __is_sorted_sanity_check;
				typedef typename conditional_<
					typename is_empty_<T>::bool_,
					midnight::core::bool_<true>,
					__internal_is_sorted<typename T::current_type, typename T::rest, C>
				>::type::type type;
				static constexpr decltype(type::value) value = type::value;
				typedef midnight::core::bool_<value> bool_;
			};

			template<class I, class E, class S, template<typename, typename> class A, template<typename, typename> class C> struct __internal_stream {
				typedef typename conditional_<
					typename C<I, E>::type,
					__internal_stream<typename A<I, S>::type, E, S, A, C>,
					nil_
				>::type next_stream;
				typedef I current_type;
				typedef __internal_stream<I, E, S, A, C> type;
			};

			template<class I, class E, class S = int_<1>, template<typename, typename> class A = add_, template<typename, typename> class C = less_than_>
				struct stream_ {
				typedef __internal_stream<I, E, S, A, C> __stream_template;
				typedef typename __stream_template::next_stream next_stream;
				typedef typename __stream_template::current_type current_type;
				typedef typename __stream_template::type type;
			};

			template<class S, template<typename> class P, template<typename> class C, class T, class I, class N> struct __internal_map_stream {
				typedef typename conditional_<
					typename logical_or_<
						typename equals_<I, N>::bool_,
						typename is_nil_<typename S::next_stream>::bool_
					>::bool_,
					T,
					__internal_map_stream<
						typename S::next_stream,
						P,
						C, 
						typename append_<
							T, 
							typename conditional_<
								typename C<typename S::current_type>::type,
								typename P<typename S::current_type>::type,
								typename S::current_type
							>::type
						>::type,
						typename add_<I, int_<1>>::int_,
						N
					>
				>::type::type type;
			};

			template<class S, template<typename> class P, template<typename> class C = accept_, class N = int_<-1>> struct map_stream_ {
				typedef typename __internal_map_stream<S, P, C, nil_, int_<0>, N>::type type;
			};

			template<class S, template<typename> class P, class T, class I, class N> struct __internal_filter_stream {
				typedef typename conditional_<
					typename logical_or_<
						typename equals_<I, N>::bool_,
						typename is_nil_<typename S::next_stream>::bool_
					>::bool_,
					T,
					typename conditional_<
						typename P<typename S::current_type>::type,
						__internal_filter_stream<
							typename S::next_stream,
							P,
							typename append_<T, typename S::current_type>::type,
							typename add_<I, int_<1>>::int_,
							N
						>,
						__internal_filter_stream<
							typename S::next_stream,
							P,
							T,
							typename add_<I, int_<1>>::int_,
							N
						>
					>::type
				>::type::type type;
			};

			template<class S, template<typename> class P, class N = int_<-1>> struct filter_stream_ {
				typedef typename __internal_filter_stream<S, P, nil_, int_<0>, N>::type type;
			};

			template<class S, class I, class N> struct __internal_advance_stream {
				typedef typename fail_<
					typename less_than_or_equal_to_<N, int_<1>>::bool_
				>::type __internal_advance_stream_sanity_check;
				typedef typename conditional_<
					typename greater_than_or_equal_to_<I, N>::bool_,
					S,
					__internal_advance_stream<typename S::next_stream, typename add_<I, int_<1>>::int_, N>
				>::type::type type;
			};

			template<class S, class N = int_<1>> struct advance_stream_ {
				typedef typename __internal_advance_stream<S, int_<0>, N>::type type;
			};

			template<class B, class S, template<typename, typename> class R, class I, class N, template<typename> class A> struct __internal_reduce_stream {
				typedef typename conditional_<
					typename logical_or_<
						typename equals_<I, N>::bool_,
						typename is_nil_<typename S::next_stream>::bool_
					>::bool_,
					B,
					__internal_reduce_stream<
						typename A<typename R<B, typename S::current_type>::type>::type,
						typename S::next_stream,
						R,
						typename add_<I, int_<1>>::int_,
						N,
						A
					>
				>::type::type type;
			};

			template<class B, class S, template<typename, typename> class R, class N = int_<-1>, template<typename> class A = identity_> struct reduce_stream_ {
				typedef typename __internal_reduce_stream<B, S, R, int_<0>, N, A>::type type;
			};

			template<class T, class R> struct __internal_reverse {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					__internal_reverse<typename T::rest, typename insert_<R, int_<0>, typename T::current_type>::type>
				>::type::type type;
			};

			template<class T, class I, class N> struct __internal_cycle {
				typedef typename conditional_<
					typename greater_than_or_equal_to_<I, N>::bool_,
					int_<0>,
					I
				>::type __real_index;
				typedef typename add_<__real_index, int_<1>>::int_ __next_index;
				typedef typename at_<T, __real_index>::type current_type;
				typedef __internal_cycle<T, __next_index, N> next_stream;
				typedef __internal_cycle<T, __real_index, N> type;
			};

			template<class T> struct cycle_ {
				typedef typename fail_<
					typename not_<
						typename is_type_list_<T>::bool_
					>::bool_
				>::type __cycle_sanity_check;
				typedef typename len_<T>::length __type_list_length;
				typedef __internal_cycle<T, int_<0>, __type_list_length> __base_internal_cycle;
				typedef typename __base_internal_cycle::current_type current_type;
				typedef typename __base_internal_cycle::next_stream next_stream;
				typedef typename __base_internal_cycle::type type;
			};
		
			template<class V> struct repeat_ {
				typedef V current_type;
				typedef repeat_<V> next_stream;
				typedef repeat_<V> type;
			};

			template<class T> struct reverse_ {
				typedef typename __internal_reverse<T, nil_>::type type;
			};

			template<class T, class R> struct __internal_flatten;

			template<class T> struct __internal_flatten_helper {
				typedef typename conditional_<
					typename is_type_list_<T>::bool_,
					__internal_flatten<T, nil_>,
					T
				>::type::type type;
			};

			template<class T, class R> struct __internal_flatten {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename logical_and_<
							is_type_list_<typename T::current_type>,
							not_<typename is_nil_<typename T::current_type>::bool_>
						>::bool_,
						__internal_flatten<
							typename T::rest,
							typename append_all_<
								R,
								typename __internal_flatten_helper<typename T::current_type>::type
							>::type
						>,
						__internal_flatten<
							typename T::rest,
							typename append_<R, typename T::current_type>::type
						>
					>::type
				>::type::type type;
			};

			template<class T> struct flatten_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __flatten_sanity_check;
				typedef typename __internal_flatten<T, nil_>::type type;
			};
			
			template<class T, class U, class R, template<typename, typename> class C> struct __internal_sort_merge {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					typename append_all_<R, U>::type,
					typename conditional_<
						typename is_end_<U>::bool_,
						typename append_all_<R, T>::type,
						typename conditional_<
							typename C<typename T::current_type, typename U::current_type>::type,
							__internal_sort_merge<
								typename T::rest,
								U,
								typename append_<R, typename T::current_type>::type,
								C
							>,
							__internal_sort_merge<
								T,
								typename U::rest,
								typename append_<R, typename U::current_type>::type,
								C
							>
						>::type
					>::type
				>::type::type type;
			};

			template<class U, class R, template<typename, typename> class C> struct __internal_sort_merge<nil_, U, R, C> {
				typedef typename append_all_<R, U>::type type;
			};

			template<class T, class R, template<typename, typename> class C> struct __internal_sort_merge<T, nil_, R, C> {
				typedef typename append_all_<R, T>::type type;
			};

			template<class R, template<typename, typename> class C> struct __internal_sort_merge<nil_, nil_, R, C> {
				typedef R type;
			};

			template<class T, class U, template<typename, typename> class C = less_than_or_equal_to_> struct merge_ {
				typedef typename __internal_sort_merge<T, U, nil_, C>::type type;
			};

			template<class T, template<typename, typename> class C = less_than_or_equal_to_> struct sort_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __sort_sanity_check;
				typedef typename divide_<typename len_<T>::int_, int_<2>>::int_ __T_half;
				typedef typename len_<T>::int_ __T_len;
				typedef typename sslice_<T, __T_half>::type __left_slice;
				typedef typename slice_<T, __T_half, __T_len>::type __right_slice;
				typedef typename conditional_<
					typename logical_or_<
						is_end_<T>,
						equals_<__T_len, int_<0>>
					>::bool_,
					T,
					__internal_sort_merge<
						typename sort_<__left_slice, C>::type,
						typename sort_<__right_slice, C>::type,
						nil_,
						C
					>
				>::type::type type;
			};

			template<template<typename, typename> class C> struct sort_<nil_, C> {
				typedef nil_ type;
			};

			template<class V, template<typename, typename> class C> struct sort_<type_list_<V>, C> {
				typedef type_list_<V> type;
			};

			template<class T, class S, class L, template<typename, typename> class E = equals_, template<typename, typename> class C = less_than_or_equal_to_>
				struct __internal_binary_search {
				typedef typename fail_<
					typename not_<typename is_sorted_<T, C>::bool_>::bool_
				>::type __binary_search_sanity_check;
				typedef typename len_<T>::length __T_len;
				typedef typename divide_<__T_len, midnight::core::int_<2>>::int_ __T_half;
				typedef typename sslice_<T, __T_half>::type __left_slice;
				typedef typename slice_<T, typename add_<__T_half, midnight::core::int_<1>>::int_, __T_len>::type __right_slice;
				typedef typename at_<T, __T_half>::type __T_current;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::int_<-1>,
					typename conditional_<
						typename E<__T_current, S>::bool_,
						typename add_<L, __T_half>::int_,
						typename conditional_<
							typename C<S, __T_current>::type,
							__internal_binary_search<__left_slice, S, L, E, C>,
							__internal_binary_search<__right_slice, S, typename add_<L, add_<__T_half, midnight::core::int_<1>>>::int_, E, C>
						>::type
					>::type
				>::type::type type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class S, class L, template<typename, typename> class E, template<typename, typename> class C> struct __internal_binary_search<nil_, S, L, E, C> {
				typedef midnight::core::int_<-1> type, int_;
				static constexpr decltype(type::value) value = type::value;
			};
	
			template<class V, class S, class L, template<typename, typename> class E, template<typename, typename> class C>
				struct __internal_binary_search<type_list_<V>, S, L, E, C> {
				typedef typename conditional_<
					typename E<V, S>::type,
					L,
					midnight::core::int_<-1>
				>::type type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class S, template<typename, typename> class E = equals_, template<typename, typename> class C = less_than_or_equal_to_> struct binary_search_ {
				typedef typename __internal_binary_search<T, S, midnight::core::int_<0>, E, C>::type type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class P, class A, template<typename, typename> class C = types_equal_> struct replace_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __replace_sanity_check;
				typedef typename index_of_<T, P, C>::type __index_to_replace;
				typedef typename conditional_<
					typename greater_than_or_equal_to_<__index_to_replace, int_<0>>::bool_,
					typename insert_<typename remove_<T, __index_to_replace>::type, __index_to_replace, A>::type,
					T
				>::type::type type;
			};

			template<class T, class P, class A, class R, template<typename, typename> class C> struct __internal_replace_all {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __internal_replace_all_sanity_check;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename C<P, typename T::current_type>::type,
						__internal_replace_all<
							typename T::rest,
							P, A,
							typename append_<R, A>::type,
							C
						>,
						__internal_replace_all<
							typename T::rest,
							P, A, 
							typename append_<R, typename T::current_type>::type,
							C
						>
					>::type
				>::type::type type;
			};

			template<class P, class A, class R, template<typename, typename> class C> struct __internal_replace_all<nil_, P, A, R, C> {
				typedef R type;
			};

			template<class T, class P, class A, template<typename, typename> class C = types_equal_> struct replace_all_ {
				typedef typename __internal_replace_all<T, P, A, nil_, C>::type type;
			};

			template<class T, template<typename> class P, class A, class R> struct __internal_replace_if {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __internal_replace_if_sanity_check;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename P<typename T::current_type>::type,
						__internal_replace_if<
							typename T::rest,
							P, A,
							typename append_<R, A>::type
						>,
						__internal_replace_if<
							typename T::rest,
							P, A,
							typename append_<R, typename T::current_type>::type
						>
					>::type
				>::type::type type;
			};

			template<template<typename> class P, class A, class R> struct __internal_replace_if<nil_, P, A, R> {
				typedef R type;
			};

			template<class T, template<typename> class P, class A> struct replace_if_ {
				typedef typename __internal_replace_if<T, P, A, nil_>::type type;
			};

			template<class T, class P, class R, template<typename, typename> class C> struct __internal_remove_all {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __internal_remove_all_sanity_check;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename C<P, typename T::current_type>::type,
						__internal_remove_all<
							typename T::rest,
							P,
							R,
							C
						>,
						__internal_remove_all<
							typename T::rest,
							P,
							typename append_<R, typename T::current_type>::type,
							C
						>
					>::type
				>::type::type type;
			};

			template<class P, class R, template<typename, typename> class C> struct __internal_remove_all<nil_, P, R, C> {
				typedef R type;
			};

			template<class T, class P, template<typename, typename> class C = types_equal_> struct remove_all_ {
				typedef typename __internal_remove_all<T, P, nil_, C>::type type;
			};

			template<class T, template<typename> class P, class R> struct __internal_remove_if {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __internal_remove_if_sanity_check;
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename P<typename T::current_type>::type,
						__internal_remove_if<
							typename T::rest,
							P,
							R
						>,
						__internal_remove_if<
							typename T::rest,
							P,
							typename append_<R, typename T::current_type>::type
						>
					>::type
				>::type::type type;
			};

			template<template<typename> class P, class R> struct __internal_remove_if<nil_, P, R> {
				typedef R type;
			};

			template<class T, template<typename> class P> struct remove_if_ {
				typedef typename __internal_remove_if<T, P, nil_>::type type;
			};

			template<class T, class N = int_<1>> struct advance_ {
				typedef typename fail_<
					typename less_than_<N, int_<0>>::bool_
				>::type __advance_sanity_check;
				typedef typename conditional_<
					typename logical_or_<
						typename is_end_<T>::bool_,	
						equals_<N, int_<0>>
					>::bool_,
					T,
					advance_<typename T::rest, sub_<N, int_<1>>>
				>::type::type type;
			};
			
			template<class T, class P, class I, template<typename, typename> class C> struct __internal_adjacent {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::int_<-1>,
					typename conditional_<
						typename C<P, typename T::current_type>::type,
						I,
						__internal_adjacent<typename T::rest, typename T::current_type, add_<I, midnight::core::int_<1>>, C>
					>::type
				>::type::type type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class P, class I, template<typename, typename> class C> struct __internal_adjacent<nil_, P, I, C> {
				typedef midnight::core::int_<-1> type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, template<typename, typename> class C = types_equal_> struct adjacent_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __adjacent_sanity_check;
				typedef typename __internal_adjacent<typename T::rest, typename T::current_type, midnight::core::int_<0>, C>::type type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<template<typename, typename> class C> struct adjacent_<nil_, C> {
				typedef midnight::core::int_<-1> type, int_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class R, template<typename, typename> class C> struct __internal_is_unique {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					midnight::core::bool_<true>,
					typename conditional_<
						typename not_equals_<
							typename index_of_<R, typename T::current_type, C>::type,
							int_<-1>
						>::bool_,
						midnight::core::bool_<false>,
						__internal_is_unique<
							typename T::rest,
							typename append_<R, typename T::current_type>::type,
							C
						>
					>::type
				>::type::type type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class R, template<typename, typename> class C> struct __internal_is_unique<nil_, R, C> {
				typedef midnight::core::bool_<true> bool_, type;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, template<typename, typename> class C = types_equal_> struct is_unique_ {
				typedef typename fail_<
					typename not_<typename is_type_list_<T>::bool_>::bool_
				>::type __is_unique_sanity_check;
				typedef typename __internal_is_unique<T, nil_, C>::type type, bool_;
				static constexpr decltype(type::value) value = type::value;
			};

			template<class T, class R, template<typename, typename> class C> struct __internal_unique {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename not_equals_<
							typename index_of_<R, typename T::current_type, C>::type,
							int_<-1>
						>::type,
						__internal_unique<
							typename T::rest,
							R,
							C
						>,
						__internal_unique<
							typename T::rest,
							typename append_<R, typename T::current_type>::type,
							C
						>
					>::type
				>::type::type type;
			};

			template<class R, template<typename, typename> class C> struct __internal_unique<nil_, R, C> {
				typedef R type;
			};

			template<class T, template<typename, typename> class C = types_equal_> struct unique_ {
				typedef typename __internal_unique<T, nil_, C>::type type;
			};

			template<template<typename, typename> class F, class A, class B, class R> struct __internal_zip {
				typedef typename conditional_<
					typename logical_or_<
						typename is_end_<A>::bool_,
						typename is_end_<B>::bool_
					>::bool_,
					R,
					__internal_zip<
						F,
						typename A::rest,
						typename B::rest,
						typename append_<R, typename F<typename A::current_type, typename B::current_type>::type>::type
					>
				>::type::type type;
			};

			template<template<typename, typename> class F, class R> struct __internal_zip<F, nil_, nil_, R> {
				typedef R type;
			};

			template<template<typename, typename> class F, class A, class B> struct zip_ {
				typedef typename fail_<
					typename not_equals_<
						typename len_<A>::length,
						typename len_<B>::length
					>::bool_
				>::type __internal_zip_sanity_check;
				typedef typename __internal_zip<F, A, B, nil_>::type type;
			};

			template<template<typename, typename, typename> class F, class A, class B, class C, class R> struct __internal_zip_3 {
				typedef typename conditional_<
					typename logical_or_<
						typename is_end_<A>::bool_,
						typename logical_or_<
							typename is_end_<B>::bool_,
							typename is_end_<C>::bool_
						>::bool_
					>::bool_,
					R,
					__internal_zip_3<
						F,
						typename A::rest,
						typename B::rest,
						typename C::rest,
						typename append_<
							R,
							typename F<
								typename A::current_type,
								typename B::current_type,
								typename C::current_type
							>::type
						>::type
					>
				>::type::type type;
			};

			template<template<typename, typename, typename> class F, class R> struct __internal_zip_3<F, nil_, nil_, nil_, R> {
				typedef R type;
			};

			template<template<typename, typename, typename> class F, class A, class B, class C> struct zip_3_ {
				typedef typename __internal_zip_3<F, A, B, C, nil_>::type type;
			};

			template<template<typename> class P, template<typename> class A, class B> struct until_ {
				typedef typename conditional_<
					typename P<B>::type,
					B,
					until_<P, A, typename A<B>::type>
				>::type::type type;
			};

			template<template<typename> class P, class R, class T> struct __internal_take_while {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					R,
					typename conditional_<
						typename P<typename T::current_type>::type,
						__internal_take_while<
							P,
							typename append_<R, typename T::current_type>::type,
							typename T::rest
						>,
						R
					>::type
				>::type::type type;
			};

			template<template<typename> class P, class R> struct __internal_take_while<P, R, nil_> {
				typedef R type;
			};

			template<template<typename> class P, class T> struct take_while_ {
				typedef typename __internal_take_while<P, nil_, T>::type type;
			};

			template<template<typename> class P, class T> struct drop_while_ {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					T,
					typename conditional_<
						typename not_<typename P<typename T::current_type>::type>::bool_,
						T,
						drop_while_<
							P,
							typename T::rest
						>
					>::type
				>::type::type type;
			};

			template<template<typename> class P> struct drop_while_<P, nil_> {
				typedef nil_ type;
			};

			template<class T, template<typename> class C, class R, class U> struct __internal_partition {
				typedef typename conditional_<
					typename is_end_<T>::bool_,
					typename make_type_list_<R, U>::type,
					typename conditional_<
						typename C<typename T::current_type>::type,
						__internal_partition<
							typename T::rest,
							C,
							typename append_<R, typename T::current_type>::type,
							U
						>,
						__internal_partition<
							typename T::rest,
							C,
							R,
							typename append_<U, typename T::current_type>::type
						>
					>::type
				>::type::type type;
				
			};

			template<template<typename> class C, class R, class U> struct __internal_partition<nil_, C, R, U> {
				typedef typename make_type_list_<R, U>::type type;
			};

			template<class T, template<typename> class C> struct partition_ {
				typedef typename __internal_partition<T, C, nil_, nil_>::type type;
				typedef typename type::current_type first_half;
				typedef typename type::rest::current_type second_half;
			};
		}
	}
}

#endif
