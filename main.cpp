#include <iostream>
#include <vector>
#include "core_types.hpp"
#include "type_list.hpp"
#include "numeric_operators.hpp"
#include "bool_operators.hpp"
#include "generic_operators.hpp"
#include "htype_list.hpp"
#include "interop.hpp"
#include "placeholders.hpp"
#include "algs.hpp"
#include "variadic_numeric_operators.hpp"
#include "variadic_bool_operators.hpp"
#include "halgs.hpp"
#include "core_interop.hpp"
#include "math.hpp"
#include "ratio.hpp"
#include "ratio_operators.hpp"
#include "ratio_numeric_operators.hpp"
#include "ratio_bool_operators.hpp"

using namespace midnight::core;
using namespace midnight::algs;
using namespace midnight::operators;
using namespace midnight::list;
using namespace midnight::voperators;
using namespace midnight::halgs;
using namespace midnight::hlist;
using namespace midnight::placeholders;
using namespace midnight::math;
using namespace midnight::math::ratio;
using namespace midnight::math::ratio::operators;

template<class T> struct lte_1_ : public less_than_or_equal_to_<T, int_<1>> {};
template<class T> struct is_int_6_ : public types_equal_<int_<6>, T> {};
template<class T> struct is_int_0_ : public types_equal_<int_<0>, T> {};
template<class T> struct double_ : public times_<T, int_<2>> {};
template<class T> struct is_even_ : public equals_<mod_<T, int_<2>>, int_<0>> {};
template<class T> struct is_odd_ : public not_<is_even_<T>> {};
template<class T> struct inc_ : public add_<T, int_<1>> {};
template<class T> struct dec_ : public sub_<T, int_<1>> {};
template<class T> struct mod_3_ : public mod_<T, int_<3>> {};
template<class T> struct x2_2_x__3 : public sub_<
							add_<
								times_<T, T>,
								times_<int_<2>, T>
							>,
							int_<3>
						> {};
template<class T> struct triple_ : public times_<T, int_<3>> {};
template<class A, class B> struct comp_lens_ : public
	less_than_or_equal_to_<typename list::len_<A>::length, typename list::len_<B>::length> {};
template<class T> struct is_mod_3_ : public equals_<mod_3_<T>, I_(0)> {};
template<class T> struct six_times_lt_100_ : public less_than_<times_<T, I_(6)>, I_(100)> {};

int main(int argc, char* argv[]) {
	typedef typename make_type_list_<int_<4>, int_<8>, int_<7>, nil_, int_<6>, nil_, bool_<false>>::type my_list;
	typedef typename make_type_list_<int_<6>, int_<6>, int_<6>>::type my_list_2;
	typedef typename list::append_<my_list_2, int_<-1>>::type my_list_3;
	typedef typename list::insert_<my_list_3, sub_<list::len_<my_list_3>::length, int_<1>>, int_<0>>::type my_list_4;
	std::cout << my_list_2{} << '\n';
	std::cout << list::all_<my_list_2, is_int_6_>::value << '\n';
	std::cout << list::any_<my_list_2, is_int_6_>::value << '\n';
	std::cout << my_list_3{} << '\n';
	std::cout << list::all_<my_list_3, is_int_6_>::value << '\n';
	std::cout << list::any_<my_list_3, is_int_6_>::value << '\n';
	std::cout << my_list_4{} << '\n';
	std::cout << list::len_<my_list_4>::int_{} << '\n';
	typedef list::remove_<my_list_4, int_<3>> removed_my_list_4;
	typedef typename removed_my_list_4::type my_list_5;
	typedef typename removed_my_list_4::removed_type val;
	std::cout << my_list_5{} << ' ' << val{} << '\n';
	typedef typename list::insert_<my_list_5, int_<3>, int_<0>>::type my_list_6;
	std::cout << my_list_6{} << '\n';
	typedef typename list::index_of_<my_list_6, int_<-5>>::int_ index;
	std::cout << index{} << '\n';
	typedef typename list::insert_<my_list_6, int_<2>, my_list>::type my_list_7;
	std::cout << my_list_7{} << '\n';
	typedef typename list::index_of_<my_list_7, my_list>::int_ index_2;
	std::cout << index_2{} << '\n';
	typedef typename list::remove_<my_list_7, int_<2>> removed_my_list_7;
	typedef typename removed_my_list_7::type my_list_8;
	typedef typename removed_my_list_7::removed_type val_2;
	std::cout << my_list_8{} << '\n';
	std::cout << val_2{} << '\n';
	typedef typename list::remove_<my_list_8, list::index_of_<my_list_8, int_<0>>::int_> removed_my_list_8;
	typedef typename removed_my_list_8::type my_list_9;
	typedef typename removed_my_list_8::removed_type val_3;
	std::cout << my_list_9{} << '\n';
	std::cout << val_3{} << '\n';
	typedef typename list::none_<my_list_9, is_int_0_>::type val_4;
	std::cout << val_4{} << '\n';
	typedef typename list::insert_<my_list_9, int_<2>, nil_>::type my_list_10;
	std::cout << my_list_10{} << '\n';
	typedef typename list::remove_type_<my_list_10, nil_> removed_my_list_10;
	typedef typename removed_my_list_10::type my_list_11;
	typedef typename removed_my_list_10::removed_index val_5;
	std::cout << my_list_11{} << '\n';
	std::cout << val_5{} << '\n';
	std::cout << add_<size_t_<12>, size_t_<23>>::int_{} << ' ' << size_t_<3>{} << ' ' << char_<'r'>{} << '\n';
	typedef typename list::insert_<my_list_11, int_<2>, size_t_<12>>::type my_list_12;
	std::cout << my_list_12{} << '\n';
	typedef typename list::insert_<my_list_12, int_<2>, int_<0>>::type my_list_13;
	std::cout << my_list_13{} << '\n';
	typedef typename list::filter_<my_list_13, truthy_>::type my_list_14;
	std::cout << my_list_14{} << '\n';
	typedef typename list::reduce_left_<int_<1>, my_list_14, divide_>::type val_6;
	std::cout << val_6{} << '\n';
	std::cout << list::is_empty_<my_list>::type{} << ' ' << list::is_empty_<nil_>::type{} << '\n';
	typedef typename list::fill_<int_<2>, int_<10>>::type my_list_15;
	std::cout << my_list_15{} << '\n';
	typedef typename list::srange_<int_<100>>::type my_list_16;
	std::cout << my_list_16{} << '\n';
	typedef typename list::where_<my_list_16, is_even_>::type my_list_17;
	std::cout << my_list_17{} << '\n';
	typedef typename list::from_<my_list_16, my_list_17>::type my_list_18;
	std::cout << my_list_18{} << '\n';
	typedef typename list::filter_<my_list_16, is_odd_>::type my_list_19;
	std::cout << my_list_19{} << '\n';
	typedef typename list::range_<int_<0>, int_<101>>::type my_list_20;
	std::cout << my_list_20{} << '\n';
	typedef typename list::slice_<my_list_20, int_<0>, typename list::len_<my_list_20>::length, int_<10>>::type my_list_21;
	std::cout << my_list_21{} << '\n';
	typedef typename list::slice_<my_list_21, int_<1>, int_<4>>::type my_list_22;
	std::cout << my_list_22{} << '\n';
	std::cout << list::is_int_list_<my_list_22>::bool_{} << ' ' << list::is_int_list_<my_list>::bool_{} << '\n';
	std::cout << list::is_sorted_<my_list_3>::bool_{} << ' ' << list::is_sorted_<my_list_20>::bool_{} << ' ' << list::is_sorted_<nil_>::bool_{} << ' '
		<< list::is_sorted_<my_list_3, greater_than_or_equal_to_>::bool_{} << '\n';
	typedef typename list::stream_<int_<1>, int_<10000>> stream_1;
	typedef typename list::map_stream_<stream_1, double_, accept_, int_<100>>::type mapped_stream_1;
	std::cout << mapped_stream_1{} << '\n';
	typedef typename list::filter_stream_<typename list::advance_stream_<stream_1, int_<10>>::type, is_even_, int_<100>>::type filtered_stream_1;
	std::cout << filtered_stream_1{} << '\n';
	typedef typename list::stream_<int_<0>, int_<10>> stream_2;
	typedef typename list::map_stream_<stream_2, double_>::type mapped_stream_2;
	std::cout << mapped_stream_2{} << '\n';
	typedef typename list::reduce_stream_<int_<0>, stream_1, add_, int_<100>, inc_>::type reduced_stream_1;
	std::cout << reduced_stream_1{} << '\n';
	typedef typename list::reverse_<mapped_stream_2>::type reversed_mapped_stream_2;
	std::cout << reversed_mapped_stream_2{} << '\n';
	typedef typename list::stream_<int_<1>, int_<2>, int_<0>>::type stream_3;
	typedef typename list::map_stream_<stream_3, double_, accept_, int_<10>>::type mapped_stream_3;
	std::cout << mapped_stream_3{} << '\n';
	typedef typename list::stream_<int_<1>, int_<-1>, int_<1>, add_, not_equals_> naturals;
	std::cout << list::map_stream_<naturals, x2_2_x__3, accept_, int_<100>>::type{} << '\n';
	std::cout << vlogical_or_<bool_<false>, bool_<true>, equals_<vdivide_<int_<0>, int_<1>>, int_<1>>>::bool_{} << '\n';
	std::cout << apply_<vadd_, typename make_type_list_<int_<1>, int_<2>, vtimes_<int_<3>, int_<4>>>::type>::type{} << '\n';
	std::cout << compose_<typename make_htype_list_<vtimes_, double_, x2_2_x__3>::type, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	typedef typename make_htype_list_<double_, vtimes_>::type ops_1;
	std::cout << demux_<ops_1, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	std::cout << demux_<typename hlist::hinsert_<ops_1, int_<1>, x2_2_x__3>::type, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	typedef list::srange_<int_<10>>::type range1;
	std::cout << range1{} << '\n';
	typedef list::append_all_<range1, typename list::srange_<int_<5>>::type>::type inserted;
	std::cout << inserted{} << '\n';
	typedef typename list::map_<typename list::range_<int_<1>, int_<101>>::type, double_, is_even_>::type mapped;
	std::cout << mapped{} << '\n';
	typedef typename list::map_stream_<naturals, double_, is_odd_, int_<100>>::type mapped_naturals;
	std::cout << mapped_naturals{} << '\n';
	std::cout << list::len_<ops_1>::type{} << '\n';
	typedef typename make_htype_list_<vadd_, vsub_, vtimes_, vdivide_, vmod_>::type basic_ops;
	std::cout << hlist::hat_<basic_ops, int_<1>>::template type<int_<10>, int_<12>, int_<13>>::type{} << '\n';
	typedef typename hlist::hremove_<basic_ops, int_<1>>::type sub_removed;
	std::cout << hlist::hat_<sub_removed, int_<1>>::template type<int_<10>, int_<12>, int_<13>>::type{} << '\n';
	typedef typename make_htype_list_<vtimes_, inc_>::type partial_ops_list;
	std::cout << compose_<typename hlist::hinsert_all_<partial_ops_list, int_<1>, typename make_htype_list_<double_, x2_2_x__3>::type>::type, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	std::cout << compose_<typename hlist::happend_all_<typename hlist::hinsert_all_<partial_ops_list, int_<1>, typename make_htype_list_<double_, x2_2_x__3>::type>::type, typename make_htype_list_<inc_, dec_>::type>::type, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	std::cout << lockstep_<vadd_, double_, triple_, double_>::template type<int_<2>, int_<3>, int_<4>>::type{} << '\n';
	std::cout << list::is_type_list_<int_<2>>::bool_{} << ' ' << list::is_type_list_<my_list>::bool_{} << '\n';
	std::cout << hlist::is_htype_list_<my_list>::bool_{} << ' ' << hlist::is_htype_list_<basic_ops>::bool_{} << '\n';
	std::cout << list::filter_<typename list::srange_<int_<10>>::type, is_bool_>::type{} << '\n';
	typedef typename make_type_list_<my_list_2, my_list_3, my_list_4>::type list_of_lists;
	std::cout << list::map_<list_of_lists, list::len_>::type{} << '\n';
	std::cout << list::is_sorted_<list_of_lists, comp_lens_>::type{} << '\n';
	typedef typename list::flatten_<typename make_type_list_<int_<1>, int_<2>, my_list, int_<3>, range1>::type>::type test_flatten;
	typedef typename list::flatten_<typename make_type_list_<int_<1>, int_<2>, typename make_type_list_<int_<1>, int_<2>, my_list, int_<3>, range1>::type, nil_>::type>::type test_flatten_2;
	std::cout << test_flatten{} << '\n';
	std::cout << test_flatten_2{} << '\n';
	typedef typename list::filter_<range1, is_even_>::type range1_evens;
	typedef typename list::filter_<range1, is_odd_>::type range1_odds;
	std::cout << range1_evens{} << '\n';
	std::cout << range1_odds{} << '\n';
	typedef typename make_type_list_<int_<2>, int_<-4>, int_<1>, int_<5>, int_<3>, int_<4>, int_<10>, int_<9>, int_<7>, int_<0>, int_<6>, int_<8>>::type shuffled_list_1;
	typedef typename list::sort_<shuffled_list_1>::type sorted_list_1;
	std::cout << sorted_list_1{} << '\n';
	std::cout << list::binary_search_<sorted_list_1, int_<9>>::type{} << '\n';
	std::cout << quote_<vtimes_>::template call<int_<4>, int_<2>, int_<5>>::type{} << '\n';
	std::cout << partial_<quote_<vtimes_, int_<10>>::call>::template delay<int_<4>>::template delay<int_<5>, int_<11>>::
		template delay<int_<2>, int_<3>, int_<2>, int_<5>, int_<7>, int_<6>, int_<8>>::
		accumulate::type{} << '\n';
	std::cout << list::replace_<shuffled_list_1, int_<6>, int_<100>>::type{} << '\n';
	typedef typename make_type_list_<int_<1>, int_<0>, int_<0>, int_<1>, int_<0>, int_<1>, int_<1>, int_<2>, int_<0>, int_<2>, int_<2>, int_<1>, int_<0>, int_<1>>::type to_replace_test;
	std::cout << to_replace_test{} << '\n';
	std::cout << list::replace_all_<to_replace_test, int_<0>, bool_<true>>::type{} << '\n';
	std::cout << list::replace_if_<to_replace_test, lte_1_, nil_>::type{} << '\n';
	std::cout << list::remove_all_<to_replace_test, int_<1>>::type{} << '\n';
	std::cout << my_list_4{} << '\n';
	std::cout << list::remove_if_<typename list::insert_<my_list_4, int_<1>, int_<5>>::type, is_int_6_>::type{} << '\n';
	std::cout << list::map_stream_<naturals, identity_, accept_, int_<10>>::type{} << '\n';
	std::cout << list::reduce_right_<int_<0>, typename list::map_stream_<naturals, identity_, accept_, int_<10>>::type, bind_<sub_, _1, _0>::bind::type>::type{} << '\n';
	std::cout << my_list{} << '\n';	
	std::cout << list::advance_<my_list, int_<2>>::type{} << '\n';
	typedef typename list::remove_all_<list::insert_<typename list::insert_<my_list_4, int_<2>, int_<7>>::type, int_<1>, int_<5>>::type, int_<5>>::type my_list_4_modified;
	std::cout << my_list_4_modified{} << '\n';
	std::cout << list::adjacent_<my_list_4_modified, equals_>::type{} << '\n';
	typedef typename list::replace_<my_list, nil_, void_>::type my_list_modified;
	std::cout << my_list_modified{} << '\n';
	std::cout << list::is_unique_<my_list_modified>::type{} << '\n';
	std::cout << my_list_4{} << '\n';
	std::cout << list::unique_<my_list_4>::type{} << '\n';
	std::cout << bind_<make_type_list_, _1, _0, _1, _0, _2, _0, _1>::bind::template type<int_<2>, int_<1>, int_<4>>::type{} << '\n';
	std::cout << apply_<make_type_list_, typename make_type_list_<nil_>::type>::type{} << '\n';
	std::cout << on_<vtimes_, bind_<add_, int_<2>, _0>::bind::type, int_<3>, int_<4>, int_<1>>::type{} << '\n';
	std::cout << compose_<typename make_htype_list_<vtimes_, double_, x2_2_x__3>::type, int_<10>, int_<12>, int_<13>>::type{} << '\n';
	std::cout << partial_<compose_, typename make_htype_list_<vtimes_, double_, x2_2_x__3>::type>::template delay<int_<10>, int_<12>, int_<13>>::accumulate::type{} << '\n';
	std::cout << iterate_fn_<bind_<times_, _0, int_<2>>::bind::type, int_<3>>::template type<int_<3>>::type{} << '\n';
	std::cout << iterate_<bind_<times_, _0, int_<2>>::bind::type, int_<10>, int_<1>>::type{} << '\n';
	std::cout << iterate_<bind_<times_, _0, I_(2)>::bind::type, I_(10), I_(1)>::type{} << '\n';
	typedef typename list::range_<I_(1), I_(102), I_(3)>::type test_1;
	int* arr = to_int_array_(test_1{});
	std::cout << "[ "; for(int i = 0; i < list::len_<test_1>::value; i++) std::cout << arr[i] << ' '; std::cout << ']' << '\n';
	delete arr;
	typedef typename make_type_list_<C_('H'), C_('e'), C_('l'), C_('l'), C_('o'), C_(' '), C_('W'), C_('o'), C_('r'), C_('l'), C_('d')>::type hello_world;
	char* arr2 = to_char_array_(hello_world{});
	for(int i = 0; i < list::len_<hello_world>::value; i++) std::cout << arr2[i]; std::cout << '\n';
	delete arr2;
	typedef typename make_type_list_<L_(0), L_(1), L_(2)>::type long_test;
	long* arr3 = to_long_array_(long_test{});
	std::cout << "[ "; for(int i = 0; i < list::len_<long_test>::value; i++) std::cout << arr3[i] << ' '; std::cout << ']' << '\n';
	delete arr3;
	typedef typename make_type_list_<ST_(0), ST_(1), ST_(5)>::type size_t_test;
	size_t* arr4 = to_size_t_array_(size_t_test{});
	std::cout << "[ "; for(int i = 0; i < list::len_<size_t_test>::value; i++) std::cout << arr4[i] << ' '; std::cout << ']' << '\n';
	delete arr4;
	typedef typename make_type_list_<B_(true), B_(false), B_(true), B_(true), B_(false)>::type bool_test;
	bool* arr5 = to_bool_array_(bool_test{});
	std::cout << "[ "; for(int i = 0; i < list::len_<bool_test>::value; i++) std::cout << arr5[i] << ' '; std::cout << ']' << '\n';
	delete arr5;
	std::vector<int> vec;
	to_int_container_(test_1{}, vec);
	for(int i : vec) std::cout << i << '\n';
	typedef typename list::filter_<
			typename list::srange_<I_(50)>::type,
			is_mod_3_
		>::type _50_mod_3;
	typedef typename list::srange_<I_(17)>::type _17;
	typedef typename list::map_<_17, x2_2_x__3>::type _17_1;
	std::cout << _50_mod_3{} << '\n';
	std::cout << _17{} << '\n';
	std::cout << _17_1{} << '\n';
	std::cout << list::zip_<add_, _50_mod_3, _17>::type{} << '\n';
	std::cout << list::zip_3_<bind_<vsub_, _1, _2, _3>::bind::type, _50_mod_3, _17, _17_1>::type{} << '\n';
	typedef typename make_type_list_<B_(true), V_, N_, I_(0), C_('c')>::type different_types;
	typedef typename list::cycle_<different_types>::type different_types_stream;
	typedef typename list::map_stream_<different_types_stream, identity_, accept_, I_(12)>::type mapped_different_types;
	typedef typename list::filter_stream_<different_types_stream, truthy_, I_(12)>::type filtered_different_types;
	std::cout << mapped_different_types{} << '\n';
	std::cout << filtered_different_types{} << '\n';
	typedef typename list::repeat_<I_(1)>::type ones;
	std::cout << list::reduce_stream_<I_(0), ones, add_, I_(10)>::type{} << '\n';
	std::cout << partial_<vadd_>::delay<I_(1)>::delay<I_(6)>::delay<I_(5)>::accumulate::type{} << '\n';
	std::cout << fib_<I_(10)>::type{} << '\n';
	std::cout << fact_<I_(10)>::type{} << '\n';
	std::cout << gcd_<I_(1071), I_(462)>::type{} << '\n';
	std::cout << abs_<I_(1)>::type{} << '\n';
	std::cout << divisible_<I_(15), I_(7), I_(1)>::bool_{} << '\n';
	std::cout << is_prime_<I_(101)>::type{} << '\n';
	typedef generate_integral_sequence_<typename MAKE_TL_(I_(0), I_(1))::type, vadd_> fibonacci_stream;
	typedef typename list::map_stream_<fibonacci_stream, identity_, accept_, I_(10)>::type mapped_fibonacci_stream;
	std::cout << mapped_fibonacci_stream{} << '\n';
	std::cout << pow_<I_(2), I_(9)>::int_{} << '\n';
	std::cout << perm_<I_(7), I_(6)>::int_{} << '\n';
	std::cout << comb_<I_(7), I_(6)>::int_{} << '\n';
	std::cout << gcd_<I_(2), I_(3)>::int_{} << '\n';
	std::cout << ratio_<I_(2), I_(3)>::type{} << '\n';
	std::cout << lcm_<I_(14), I_(21)>::type{} << '\n';
	std::cout << 
		radd_<
		radd_<R_(I_(1), I_(2)), R_(I_(5), I_(6))>,
		R1_(I_(1))>::type{}
	<< '\n';
	std::cout <<
		reciprocal_<rdivide_<R_(I_(1), I_(2)), R_(I_(2), I_(3))>>::type{}
	<< '\n';
	std::cout << list::until_<
				bind_<divisible_, _1, I_(2), I_(1)>::bind::type,
				bind_<divide_, _1, I_(2)>::bind::type,
				I_(400)
			>::type{} << '\n';
	std::cout << list::take_while_<
				bind_<greater_than_, C_('w'), _1>::bind::type,
				TL_(C_('h'), C_('e'), C_('l'), C_('l'), C_('o'), C_(' '), C_('w'), C_('o'), C_('r'), C_('l'), C_('d'))
			>::type{} << '\n';
	std::cout << list::drop_while_<
				six_times_lt_100_, 
				typename list::range_<I_(1), I_(21)>::type
			>::type{} << '\n';
	typedef list::partition_<shuffled_list_1,
				bind_<less_than_, _1, I_(5)>::bind::type
			> partitioned_1;
	std::cout << partitioned_1::first_half{} << '\n';
	std::cout << partitioned_1::second_half{} << '\n';
	std::cout << 
			rless_than_<
				R_(I_(1), I_(3)),
				R_(I_(1), I_(2))
			>::type{}
		<< '\n';
	return 0;
}
