#ifndef MIDNIGHT_MATH_HPP
#define MIDNIGHT_MATH_HPP

#include "core_types.hpp"
#include "algs.hpp"
#include "type_list.hpp"
#include "numeric_operators.hpp"
#include "bool_operators.hpp"
#include "generic_operators.hpp"
#include "conditional_operator.hpp"
#include "halgs.hpp"
#include "htype_list.hpp"

using namespace midnight::core;
using namespace midnight::operators;
using namespace midnight::list;
using namespace midnight::algs;
using namespace midnight::halgs;
using namespace midnight::hlist;

namespace midnight {
	namespace math {
		
		template<class F, class S, class N> struct __internal_fib {
			typedef typename conditional_<
				typename less_than_or_equal_to_<N, midnight::core::int_<0>>::bool_,
				F,
				__internal_fib<
					S,
					typename add_<F, S>::int_,
					typename sub_<N, midnight::core::int_<1>>::int_
				>
			>::type::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N> struct fib_ {
			typedef typename __internal_fib<midnight::core::int_<0>, midnight::core::int_<1>, N>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class R> struct __internal_fact {
			typedef typename conditional_<
				typename less_than_or_equal_to_<N, midnight::core::int_<0>>::bool_,
				R,
				__internal_fact<
					typename sub_<N, midnight::core::int_<1>>::int_,
					typename times_<R, N>::int_
				>
			>::type::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N> struct fact_ {
			typedef typename __internal_fact<N, midnight::core::int_<1>>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A, class B> struct gcd_ {
			typedef typename fail_<
				typename logical_or_<
					typename less_than_<A, midnight::core::int_<0>>::bool_,
					typename less_than_<B, midnight::core::int_<0>>::bool_
				>::bool_
			>::type __gcd_sanity_check;
			typedef typename conditional_<
				typename equals_<B, midnight::core::int_<0>>::bool_,
				A,
				gcd_<
					B,
					typename mod_<A, B>::int_
				>
			>::type::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A> struct gcd_<A, midnight::core::int_<0>> {
			typedef A type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N> struct abs_ {
			typedef typename conditional_<
				typename less_than_<N, midnight::core::int_<0>>::bool_,
				typename minus_<N>::int_,
				N
			>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A, class B, class R = midnight::core::int_<0>> struct divisible_ {
			typedef typename fail_<
				typename equals_<B, midnight::core::int_<0>>::bool_
			>::type __divisible_sanity_check;
			typedef typename equals_<
				typename mod_<
					A, B
				>::int_,
				R
			>::bool_ bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A, class B> struct __internal_is_prime {
			typedef typename conditional_<
				typename equals_<B, midnight::core::int_<1>>::bool_,
				midnight::core::bool_<true>,
				typename conditional_<
					typename divisible_<A, B>::bool_,
					midnight::core::bool_<false>,
					__internal_is_prime<A, typename sub_<B, midnight::core::int_<1>>::int_>
				>::type
			>::type::type type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A> struct is_prime_ {
			typedef typename conditional_<
				typename equals_<
					A, midnight::core::int_<1>
				>::bool_,	
				midnight::core::bool_<false>,
				__internal_is_prime<
					A,
					typename divide_<A, midnight::core::int_<2>>::int_
				>
			>::type::type type, bool_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class T, template<typename...> class O> struct generate_integral_sequence_ {
			typedef typename algs::list::len_<T>::length __T_length;
			typedef typename algs::list::remove_<T, midnight::core::int_<0>>::type __removed_first_T;
			typedef typename apply_<O, T>::type __next_element;
			typedef typename algs::list::append_<__removed_first_T, __next_element>::type __next_T;

			typedef typename algs::list::at_<T, midnight::core::int_<0>>::type current_type;
			typedef generate_integral_sequence_<__next_T, O> next_stream;
			typedef generate_integral_sequence_<T, O> type;
		};

		template<class B, class N> struct pow_ {
			typedef typename pow_<
					typename times_<B, B>::int_,
					typename divide_<N, midnight::core::int_<2>>::int_
				>::int_ __squared;
			typedef typename conditional_<
				typename equals_<N, midnight::core::int_<0>>::bool_,
				midnight::core::int_<1>,
				typename conditional_<
					typename equals_<N, midnight::core::int_<1>>::bool_,
					B,
					typename conditional_<
						typename divisible_<N, midnight::core::int_<2>>::bool_,
						__squared,
						typename times_<B, __squared>::int_
					>::type
				>::type
			>::type::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class B> struct pow_<B, midnight::core::int_<0>> {
			typedef midnight::core::int_<1> int_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class B> struct pow_<B, midnight::core::int_<1>> {
			typedef B int_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class R> struct comb_ {
			typedef typename fail_<
				typename greater_than_<R, N>::bool_
			>::type __comb_sanity_check;
			typedef typename divide_<
				typename fact_<N>::int_,
				typename times_<
					typename fact_<R>::int_,
					typename fact_<
						typename sub_<N, R>::int_
					>::int_
				>::int_
			>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class R> struct perm_ {
			typedef typename fail_<
				typename greater_than_<R, N>::bool_
			>::type __perm_sanity_check;
			typedef typename divide_<
				typename fact_<N>::int_,
				typename fact_<
					typename sub_<N, R>::int_
				>::int_
			>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class A, class B> struct lcm_ {
			typedef typename divide_<
				typename times_<A, B>::int_,
				typename gcd_<A, B>::int_
			>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class B, class R> struct __internal_log_floor {
			typedef typename conditional_<
					typename equals_<N, midnight::core::int_<1>>::bool_,
					R,
					__internal_log_floor<typename divide_<N, midnight::core::int_<2>>::int_, B,
								typename add_<R, midnight::core::int_<1>>::int_
						>
				>::type::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class B> struct log_floor_ {
			typedef typename fail_<
					typename logical_or_<
						less_than_or_equal_to_<N, midnight::core::int_<0>>,
						less_than_or_equal_to_<B, midnight::core::int_<0>>
					>::bool_
				>::type __log_floor_sanity_check;
			typedef typename __internal_log_floor<N, B, midnight::core::int_<0>>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class N, class I, class R> struct __internal_to_binary {
			typedef typename conditional_<
					typename less_than_<I, int_<0>>::bool_,
					R,
					typename conditional_<
						typename greater_than_or_equal_to_<
							typename sub_<N, typename pow_<int_<2>, I>::int_>::int_,
							int_<0>
						>::bool_
						,
						__internal_to_binary<
							typename sub_<N, typename pow_<int_<2>, I>::int_>::int_,
							typename sub_<I, int_<1>>::int_,
							typename algs::list::append_<R, bool_<true>>::type
						>,
						__internal_to_binary<
							N,
							typename sub_<I, int_<1>>::int_,
							typename algs::list::append_<R, bool_<false>>::type
						>
					>::type
				>::type::type type;
		};

		template<class N> struct to_binary_ {
			typedef typename fail_<
				typename less_than_<N, int_<0>>::bool_
			>::type __to_binary_sanity_check;
			typedef typename conditional_<
				typename equals_<N, int_<0>>::bool_,
				typename make_type_list_<bool_<false>>::type,
				__internal_to_binary<N, typename log_floor_<N, int_<2>>::type, nil_>
			>::type::type type;
		};

		template<class X, class Y> struct __helper_egcd {
			template<class T> struct __recombine_terms {
				typedef typename make_type_list_<
					typename algs::list::at_<T, int_<0>>::type,
					typename algs::list::at_<T, int_<2>>::type,
					typename sub_<
						typename algs::list::at_<T, int_<1>>::type,
						typename times_<
							typename divide_<
								X, Y
							>::type,
							typename algs::list::at_<T, int_<2>>::type
						>::type
					>::type
				>::type type;
			};
			typedef typename conditional_<
				typename equals_<Y, int_<0>>::bool_,
				typename make_type_list_<X, int_<1>, int_<0>>::type,
				typename __recombine_terms<
					typename __helper_egcd<
						Y,
						typename mod_<X, Y>::type
					>::type
				>::type
			>::type type;
		};
		
		template<class X> struct __helper_egcd<X, int_<0>> {
			typedef typename make_type_list_<X, int_<1>, int_<0>>::type type;
		};

		template<class X, class Y> struct egcd_ {
			typedef typename __helper_egcd<X, Y>::type list_type, type;
			typedef typename algs::list::at_<list_type, int_<0>>::type gcd_type;
			typedef typename algs::list::at_<list_type, int_<1>>::type X_coefficient_type;
			typedef typename algs::list::at_<list_type, int_<2>>::type Y_coefficient_type;
		};
	}
}

#endif
