#ifndef MIDNIGHT_VARIADIC_OPERATORS_HPP
#define MIDNIGHT_VARIADIC_OPERATORS_HPP

#include "core_types.hpp"
#include "type_list.hpp"
#include "numeric_operators.hpp"
#include "algs.hpp"

using namespace midnight::core;
using namespace midnight::list;
using namespace midnight::algs;
using namespace midnight::operators;

namespace midnight {
	namespace voperators {

		template<class F, class S, typename... R> struct vadd_ {
			typedef typename add_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vadd_type_list;
			typedef typename algs::list::reduce_right_<__base, __vadd_type_list, add_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vadd_<F, S> {
			typedef typename add_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vsub_ {
			typedef typename sub_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vsub_type_list;
			typedef typename algs::list::reduce_right_<__base, __vsub_type_list, sub_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vsub_<F, S> {
			typedef typename sub_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vtimes_ {
			typedef typename times_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vtimes_type_list;
			typedef typename algs::list::reduce_right_<__base, __vtimes_type_list, times_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vtimes_<F, S> {
			typedef typename times_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vdivide_ {
			typedef typename divide_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vdivide_type_list;
			typedef typename algs::list::reduce_right_<__base, __vdivide_type_list, divide_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vdivide_<F, S> {
			typedef typename divide_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vmod_ {
			typedef typename mod_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vmod_type_list;
			typedef typename algs::list::reduce_right_<__base, __vmod_type_list, mod_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vmod_<F, S> {
			typedef typename mod_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vshift_left_ {
			typedef typename shift_left_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vshift_left_type_list;
			typedef typename algs::list::reduce_right_<__base, __vshift_left_type_list, shift_left_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vshift_left_<F, S> {
			typedef typename shift_left_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vshift_right_ {
			typedef typename shift_right_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vshift_right_type_list;
			typedef typename algs::list::reduce_right_<__base, __vshift_right_type_list, shift_right_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vshift_right_<F, S> {
			typedef typename shift_right_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vbitwise_and_ {
			typedef typename bitwise_and_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vbitwise_and_type_list;
			typedef typename algs::list::reduce_right_<__base, __vbitwise_and_type_list, bitwise_and_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vbitwise_and_<F, S> {
			typedef typename bitwise_and_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vbitwise_or_ {
			typedef typename bitwise_or_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vbitwise_or_type_list;
			typedef typename algs::list::reduce_right_<__base, __vbitwise_or_type_list, bitwise_or_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};
		
		template<class F, class S> struct vbitwise_or_<F, S> {
			typedef typename bitwise_or_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S, typename... R> struct vbitwise_xor_ {
			typedef typename bitwise_xor_<F, S>::int_ __base;
			typedef typename make_type_list_<R...>::type __vbitwise_xor_type_list;
			typedef typename algs::list::reduce_right_<__base, __vbitwise_xor_type_list, bitwise_xor_>::type type, int_;
			static constexpr decltype(type::value) value = type::value;
		};

		template<class F, class S> struct vbitwise_xor_<F, S> {
			typedef typename bitwise_xor_<F, S>::int_ type, int_;
			static constexpr decltype(type::value) value = type::value;
		};
	}
}

#endif
