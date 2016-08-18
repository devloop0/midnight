#ifndef MIDNIGHT_RATIO_NUMERIC_OPERATORS_HPP
#define MIDNIGHT_RATIO_NUMERIC_OPERATORS_HPP

#include "ratio.hpp"
#include "math.hpp"
#include "core_types.hpp"
#include "ratio_operators.hpp"
#include "generic_operators.hpp"
#include "numeric_operators.hpp"

using namespace midnight::math::ratio;
using namespace midnight::math;
using namespace midnight::core;
using namespace midnight::operators;

namespace midnight {
	namespace math {
		namespace ratio {
			namespace operators {
			
				template<class R1, class R2> struct radd_ {
					typedef decltype(R1{} + R2{}) type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(numerator::value) numerator_value = numerator::value;
					static constexpr decltype(denominator::value) denominator_value = denominator::value;
					constexpr radd_() {}
				};

				template<class R1, class R2> struct rsub_ {
					typedef decltype(R1{} - R2{}) type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(numerator::value) numerator_value = numerator::value;
					static constexpr decltype(denominator::value) denominator_value = denominator::value;
					constexpr rsub_() {}
				};

				template<class R1, class R2> struct rtimes_ {
					typedef decltype(R1{} * R2{}) type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(numerator::value) numerator_value = numerator::value;
					static constexpr decltype(denominator::value) denominator_value = denominator::value;
					constexpr rtimes_() {}
				};

				template<class R1, class R2> struct rdivide_ {
					typedef decltype(R1{} / R2{}) type, ratio_;
					typedef typename type::numerator numerator;
					typedef typename type::denominator denominator;
					static constexpr decltype(numerator::value) numerator_value = numerator::value;
					static constexpr decltype(denominator::value) denominator_value = denominator::value;
					constexpr rdivide_() {}
				};
			}
		}
	}
}

#endif
