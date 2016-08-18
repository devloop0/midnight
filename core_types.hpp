#ifndef MIDNIGHT_CORE_TYPES_HPP
#define MIDNIGHT_CORE_TYPES_HPP

namespace midnight {
	namespace core {

		template<bool B> struct bool_ {
			static constexpr bool value = B;
			typedef bool_<B> type;
			constexpr bool_() {}
		};

		template<int N> struct int_ {
			static constexpr int value = N;
			typedef int_<N> type;
			constexpr int_() {}
		};

		struct void_ {
			static constexpr decltype(nullptr) value = nullptr;
			typedef void_ type;
			constexpr void_() {}
		};

		template<char C> struct char_ {
			static constexpr char value = C;
			typedef char_<C> type;
			constexpr char_() {}
		};

		template<unsigned int S> struct size_t_ {
			static constexpr unsigned int value = S;
			typedef size_t_<S> type;
			constexpr size_t_() {}
		};

		template<long L> struct long_ {
			static constexpr long value = L;
			typedef long_<L> type;
			constexpr long_() {}
		};
	}
}

#endif
