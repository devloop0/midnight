#ifndef MIDNIGHT_RATIO_HPP
#define MIDNIGHT_RATIO_HPP

#include "core_types.hpp"
#include "generic_operators.hpp"
#include "math.hpp"
#include "numeric_operators.hpp"
#include "bool_operators.hpp"
#include "conditional_operator.hpp"
#include "algs.hpp"

using namespace midnight::core;
using namespace midnight::math;
using namespace midnight::operators;

namespace midnight {
	namespace math {
		namespace ratio {
			
			template<class N, class D = int_<1>> struct ratio_ {
				typedef typename fail_<
					typename equals_<D, int_<0>>::bool_
				>::type __ratio_sanity_check;
				typedef N numerator;
				typedef D denominator;
				static constexpr decltype(numerator::value) numerator_value = numerator::value;
				static constexpr decltype(denominator::value) denominator_value = denominator::value;
				typedef ratio_<N, D> type;
			};

			namespace operators {

				template<class R1> struct simplify_ {
					typedef typename abs_<typename R1::numerator>::type __numerator;
					typedef typename abs_<typename R1::denominator>::type __denominator;
					typedef typename gcd_<
							__numerator,
							__denominator
						>::type __to_divide_by;
					typedef typename divide_<typename R1::numerator, __to_divide_by>::int_ __reduced_numerator;
					typedef typename divide_<typename R1::denominator, __to_divide_by>::int_ __reduced_denominator;
					typedef typename conditional_<
						typename less_than_<__reduced_denominator, int_<0>>::bool_,
						midnight::math::ratio::ratio_<
							typename minus_<__reduced_numerator>::int_,
							typename minus_<__reduced_denominator>::int_
						>,
						midnight::math::ratio::ratio_<
							__reduced_numerator,
							__reduced_denominator
						>
					>::type type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(type::numerator_value) numerator_value = type::numerator_value;
					static constexpr decltype(type::denominator_value) denominator_value = type::denominator_value;
				};

				template<class R1> struct reciprocal_ {
					typedef midnight::math::ratio::ratio_<
							typename R1::denominator,
							typename R1::numerator
						> type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(type::numerator_value) numerator_value = type::numerator_value;
					static constexpr decltype(type::denominator_value) denominator_value = type::denominator_value;
				};
			}
		}
	}
}

#endif
