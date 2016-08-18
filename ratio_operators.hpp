#ifndef MIDNIGHT_RATIO_OPERATORS_HPP
#define MIDNIGHT_RATIO_OPERATORS_HPP

#include "math.hpp"
#include "ratio.hpp"
#include "core_types.hpp"
#include "generic_operators.hpp"
#include "numeric_operators.hpp"

using namespace midnight::core;
using namespace midnight::math;
using namespace midnight::math::ratio;
using namespace midnight::operators;
using namespace midnight::math::ratio::operators;

namespace midnight {
	namespace math {
		namespace ratio {

			template<class R1, class R2, template<class, class> class O,
				typename __resulting_denominator = typename lcm_<
										typename R1::denominator,
										typename R2::denominator
									>::int_,
				typename __1_numerator_factor = typename divide_<
										__resulting_denominator,
										typename R1::denominator
									>::int_,
				typename __2_numerator_factor = typename divide_<
										__resulting_denominator,
										typename R2::denominator
									>::int_,
				typename __1_numerator = typename times_<__1_numerator_factor, typename R1::numerator>::int_,
				typename __2_numerator = typename times_<__2_numerator_factor, typename R2::numerator>::int_,
				typename __resulting_numerator = typename O<__1_numerator, __2_numerator>::int_,
				typename __result = typename simplify_<ratio_<__resulting_numerator, __resulting_denominator>>::type
			> constexpr __result __internal_adder_subber_helper(R1, R2) {
				return __result{};
			}

			template<class R1, class R2> constexpr decltype(
				__internal_adder_subber_helper<R1, R2, add_>(R1{}, R2{})
			) operator+(R1 r1, R2 r2) {
				return __internal_adder_subber_helper<R1, R2, add_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(
				__internal_adder_subber_helper<R1, R2, sub_>(R1{}, R2{})
			) operator-(R1 r1, R2 r2) {
				return __internal_adder_subber_helper<R1, R2, sub_>(r1, r2);
			}

			template<class R1, class R2,
				typename __resulting_numerator = typename times_<
									typename R1::numerator,
									typename R2::numerator
								>::type,
				typename __resulting_denominator = typename times_<
									typename R1::denominator,
									typename R2::denominator
								>::type,
				typename __result = typename simplify_<
								ratio_<
									__resulting_numerator,	
									__resulting_denominator
								>
							>::type
			> constexpr __result operator*(R1, R2) {
				return __result{};
			}

			template<class R1, class R2,
				typename __resulting_numerator = typename times_<
									typename R1::numerator,
									typename R2::denominator
								>::type,
				typename __resulting_denominator = typename times_<
									typename R1::denominator,
									typename R2::numerator
								>::type,
				typename __result = typename simplify_<
									ratio_<
										__resulting_numerator,
										__resulting_denominator
									>
								>::type
			> constexpr __result operator/(R1, R2) {
				return __result{};
			}

			template<class R1, class R2, template<typename, typename> class C,
					typename __lcm = typename lcm_<
								typename R1::denominator,
								typename R2::denominator
							>::int_,
					typename __1_numerator_factor = typename divide_<
										__lcm,
										typename R1::denominator
									>::int_,
					typename __2_numerator_factor = typename divide_<
										__lcm,
										typename R2::denominator
									>::int_,
					typename __1_numerator = typename times_<
										__1_numerator_factor,
										typename R1::numerator
									>::int_,
					typename __2_numerator = typename times_<
										__2_numerator_factor,
										typename R2::numerator
									>::int_,
					typename __result = typename C<__1_numerator, __2_numerator>::bool_
			> constexpr __result __internal_bool_operator_helper(R1, R2) {
				return __result{};
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, greater_than_>(R1{}, R2{})) operator>(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, greater_than_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, less_than_>(R1{}, R2{})) operator<(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, less_than_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, greater_than_or_equal_to_>(R1{}, R2{})) operator>=(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, greater_than_or_equal_to_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, less_than_or_equal_to_>(R1{}, R2{})) operator<=(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, less_than_or_equal_to_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, equals_>(R1{}, R2{})) operator==(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, equals_>(r1, r2);
			}

			template<class R1, class R2> constexpr decltype(__internal_bool_operator_helper<R1, R2, not_equals_>(R1{}, R2{})) operator!=(R1 r1, R2 r2) {
				return __internal_bool_operator_helper<R1, R2, not_equals_>(r1, r2);
			}
		}
	}
}

#endif
