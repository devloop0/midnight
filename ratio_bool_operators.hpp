#ifndef MIDNIGHT_RATIO_BOOL_OPERATORS_HPP
#define MIDNIGHT_RATIO_BOOL_OPERATORS_HPP

#include "ratio.hpp"
#include "ratio_operators.hpp"
#include "math.hpp"
#include "core_types.hpp"
#include "generic_operators.hpp"
#include "bool_operators.hpp"

using namespace midnight::math::ratio;
using namespace midnight::core;
using namespace midnight::operators;
using namespace midnight::math;

namespace midnight {
	namespace math {
		namespace ratio {
			namespace operators {
			
				template<class R1, class R2> struct rless_than_ {
					typedef decltype(R1{} < R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr rless_than_() {}
				};
				
				template<class R1, class R2> struct rgreater_than_ {
					typedef decltype(R1{} > R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr rgreater_than_() {}
				};

				template<class R1, class R2> struct rgreater_than_or_equal_to_ {
					typedef decltype(R1{} >= R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr rgreater_than_or_equal_to_() {}
				};
	
				template<class R1, class R2> struct rless_than_or_equal_to_ {
					typedef decltype(R1{} <= R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr rless_than_or_equal_to_() {}
				};

				template<class R1, class R2> struct requals_ {
					typedef decltype(R1{} == R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr requals_() {}
				};

				template<class R1, class R2> struct rnot_equals_ {
					typedef decltype(R1{} != R2{}) type, bool_;
					static constexpr decltype(type::value) value = type::value;
					constexpr rnot_equals_() {}
				};
			}
		}
	}
}

#endif
