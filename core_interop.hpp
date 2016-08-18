#ifndef MIDNIGHT_CORE_INTEROP_HPP
#define MIDNIGHT_CORE_INTEROP_HPP

#include "core_types.hpp"
#include "type_list.hpp"
#include "htype_list.hpp"
#include "algs.hpp"
#include "numeric_operators.hpp"
#include "bool_operators.hpp"
#include "conditional_operator.hpp"
#include "ratio.hpp"
#ifndef MIDNIGHT_NO_STD
#include <cstddef>
#endif

#define MIDNIGHT_MAKE_TYPE_WITH_ARG(T, A) T<A>
#define MIDNIGHT_MAKE_TYPE_WITH_ARGS(T, ...) T<__VA_ARGS__>

#define INT_(A) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::core::int_, A)
#define BOOL_(A) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::core::bool_, A)
#define SIZE_T_(A) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::core::size_t_, A)
#define CHAR_(A) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::core::char_, A)
#define LONG_(A) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::core::long_, A)
#define VOID_ midnight::core::void_
#define NIL_ midnight::list::nil_
#define HNIL_ MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::hlist::hnil_, )
#define HNIL_V_(...) MIDNIGHT_MAKE_TYPE_WITH_ARGS(midnight::hlist::hnil_, __VA_ARGS__)
#define RATIO_(N, D) MIDNIGHT_MAKE_TYPE_WITH_ARGS(midnight::math::ratio::ratio_, N, D)
#define RATIO_1_(N) MIDNIGHT_MAKE_TYPE_WITH_ARG(midnight::math::ratio::ratio_, N)
#define MAKE_TYPE_LIST_(...) MIDNIGHT_MAKE_TYPE_WITH_ARGS(midnight::list::make_type_list_, __VA_ARGS__)
#define TYPE_LIST_(...) typename MAKE_TYPE_LIST_(__VA_ARGS__)::type

#define I_ INT_
#define B_ BOOL_
#define ST_ SIZE_T_
#define C_ CHAR_
#define L_ LONG_
#define V_ VOID_
#define N_ NIL_
#define HN_ HNIL_
#define HNV_ HNIL_V_
#define MAKE_TL_ MAKE_TYPE_LIST_
#define TL_ TYPE_LIST_
#define R_ RATIO_
#define R1_ RATIO_1_

using namespace midnight::core;
using namespace midnight::list;
using namespace midnight::hlist;
using namespace midnight::algs;
using namespace midnight::operators;
#ifndef MIDNIGHT_NO_STD
#define MIDNIGHT_SIZE_T std::size_t
#else
#define MIDNIGHT_SIZE_T unsigned int
#endif

namespace midnight {
	namespace interop {
		
		template<class T, class A, class N> void __internal_assign_array_helper(T t, A* a, N) {
			typedef typename T::current_type T_now;
			typedef typename T::rest T_next;
			a[N::value] = T_now::value;
			typedef typename conditional_<
					typename algs::list::is_end_<T_next>::bool_,
					I_(-1),
					typename add_<N, I_(1)>::int_
				>::type N_next;
			__internal_assign_array_helper(T_next{}, a, N_next{});
		}

		template<> void __internal_assign_array_helper<nil_, int, I_(-1)>(nil_, int*, I_(-1)) {

		}

		template<> void __internal_assign_array_helper<nil_, bool, I_(-1)>(nil_, bool*, I_(-1)) {

		}

		template<> void __internal_assign_array_helper<nil_, char, I_(-1)>(nil_, char*, I_(-1)) {

		}

		template<> void
			__internal_assign_array_helper<nil_, MIDNIGHT_SIZE_T, I_(-1)>(nil_, MIDNIGHT_SIZE_T*, I_(-1)) {

		}

		template<> void __internal_assign_array_helper<nil_, long, I_(-1)>(nil_, long*, I_(-1)) {

		}

		template<class T,
				typename __internal_to_int_array_sanity_check = typename fail_<
						typename not_<typename algs::list::is_int_list_<T>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> int* to_int_array_(T) {
			int* res = new int[__internal_type_list_length::value];
			__internal_assign_array_helper(T{}, res, I_(0){});
			return res;
		}

		template<class T,
				typename __internal_to_char_array_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_char_>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> char* to_char_array_(T) {
			char* res = new char[__internal_type_list_length::value];
			__internal_assign_array_helper(T{}, res, I_(0){});
			return res;
		}

		template<class T,
				typename __internal_to_bool_array_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_bool_>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> bool* to_bool_array_(T) {
			bool* res = new bool[__internal_type_list_length::value];
			__internal_assign_array_helper(T{}, res, I_(0){});
			return res;
		}

		template<class T,
				typename __internal_to_size_t_array_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_size_t_>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> MIDNIGHT_SIZE_T* to_size_t_array_(T) {
			MIDNIGHT_SIZE_T* res = new MIDNIGHT_SIZE_T[__internal_type_list_length::value];
			__internal_assign_array_helper(T{}, res, I_(0){});
			return res;
		}

		template<class T,
				typename __internal_to_long_array_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_long_>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> long* to_long_array_(T) {
			long* res = new long[__internal_type_list_length::value];
			__internal_assign_array_helper(T{}, res, I_(0){});
			return res;
		}

		template<class T, template<typename...> class C,
			typename __internal_to_int_container_sanity_check = typename fail_<
						typename not_<typename algs::list::is_int_list_<T>::bool_>::bool_
					>::type,
				typename __internal_type_list_length = typename algs::list::len_<T>::length
		> void to_int_container_(T, C<int>& ret) {
			int* res = to_int_array_(T{});
			for(int i = 0; i < __internal_type_list_length::value; i++) ret.insert(ret.end(), res[i]);
			delete res;
		}

		template<class T, template<typename...> class C,
			typename __internal_to_char_container_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_char_>::bool_>::bool_
					>::type,
			typename __internal_type_list_length = typename algs::list::len_<T>::length
		> void to_char_container_(T, C<char>& ret) {
			char* res = to_char_array_(T{});
			for(int i = 0; i < __internal_type_list_length::value; i++) ret.insert(ret.end(), res[i]);
			delete res;
		}

		template<class T, template<typename...> class C,
			typename __internal_to_bool_container_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_bool_>::bool_>::bool_
					>::type,
			typename __internal_type_list_length = typename algs::list::len_<T>::length
		> void to_bool_container_(T, C<bool>& ret) {
			bool* res = to_bool_array_(T{});
			for(int i = 0; i < __internal_type_list_length::value; i++) ret.insert(ret.end(), res[i]);
			delete res;
		}

		template<class T, template<typename...> class C,
			typename __internal_to_size_t_container_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_size_t_>::bool_>::bool_
					>::type,
			typename __internal_type_list_length = typename algs::list::len_<T>::length
		> void to_size_t_container_(T, C<MIDNIGHT_SIZE_T>& ret) {
			MIDNIGHT_SIZE_T* res = to_size_t_container_(T{});
			for(int i = 0; i < __internal_type_list_length::value; i++) ret.insert(ret.end(), res[i]);
			delete res;
		}

		template<class T, template<typename...> class C,
			typename __internal_to_long_container_sanity_check = typename fail_<
						typename not_<typename algs::list::all_<T, is_long_>::bool_>::bool_
					>::type,
			typename __internal_type_list_length = typename algs::list::len_<T>::length
		> void to_long_container_(T, C<long>& ret) {
			long* res = to_long_array_(T{});
			for(int i = 0; i < __internal_type_list_length::value; i++) ret.insert(ret.end(), res[i]);
			delete res;
		}
	}
}

#endif
