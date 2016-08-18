#ifndef MIDNIGHT_PLACEHOLDERS_HPP
#define MIDNIGHT_PLACEHOLDERS_HPP

#include "core_types.hpp"
#include "algs.hpp"

using namespace midnight::core;
using namespace midnight::algs;

namespace midnight {
	namespace placeholders {
		
		template<class T> struct placeholder_ {
			typedef typename fail_<
				typename not_<is_int_<T>>::bool_
			>::type type;
		};
		
		template<int N> struct placeholder_<int_<N>> {
			typedef typename fail_<
				typename less_than_<midnight::core::int_<N>, midnight::core::int_<0>>::bool_
			>::type __placeholder_sanity_check;
			typedef midnight::core::int_<N> int_;
			typedef placeholder_<midnight::core::int_<N>> type;
			static constexpr decltype(int_::value) value = int_::value;
		};

		typedef placeholder_<int_<0>> _0;
		typedef placeholder_<int_<1>> _1;
		typedef placeholder_<int_<2>> _2;
		typedef placeholder_<int_<3>> _3;
		typedef placeholder_<int_<4>> _4;
		typedef placeholder_<int_<5>> _5;
		typedef placeholder_<int_<6>> _6;
		typedef placeholder_<int_<7>> _7;
		typedef placeholder_<int_<8>> _8;
		typedef placeholder_<int_<9>> _9;
		typedef placeholder_<int_<10>> _10;
		typedef placeholder_<int_<11>> _11;
		typedef placeholder_<int_<12>> _12;
		typedef placeholder_<int_<13>> _13;
		typedef placeholder_<int_<14>> _14;
		typedef placeholder_<int_<15>> _15;

		template<class T> struct is_placeholder_ {
			typedef midnight::core::bool_<false> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};

		template<int N> struct is_placeholder_<placeholder_<int_<N>>> {
			typedef midnight::core::bool_<true> bool_, type;
			static constexpr decltype(type::value) value = type::value;
		};
	}
}

#endif
