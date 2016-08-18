#if !defined(MIDNIGHT_INTEROP_HPP) && !defined(MIDNIGHT_NO_STD)
#define MIDNIGHT_INTEROP_HPP

#include "core_types.hpp"
#include "type_list.hpp"
#include "to_string.hpp"
#include "htype_list.hpp"
#include "placeholders.hpp"
#include <iostream>

using namespace midnight::interop;
using namespace midnight::hlist;
using namespace midnight::core;
using namespace midnight::list;
using namespace midnight::placeholders;

namespace midnight {
	namespace core {

		template<int N> std::ostream& operator<<(std::ostream& os, int_<N> i) {
			os << to_string(i);
			return os;
		}

		template<bool B> std::ostream& operator<<(std::ostream& os, bool_<B> b) {
			os << to_string(b);
			return os;
		}

		std::ostream& operator<<(std::ostream& os, void_ v) {
			os << to_string(v);
			return os;
		}

		template<char C> std::ostream& operator<<(std::ostream& os, char_<C> c) {
			os << to_string(c);
			return os;
		}

		template<unsigned int S> std::ostream& operator<<(std::ostream& os, size_t_<S> s) {
			os << to_string(s);
			return os;
		}
	}

	namespace list {

		std::ostream& operator<<(std::ostream& os, nil_ n)  {
			os << to_string(n);
			return os;
		}

		template<class F, class R> std::ostream& operator<<(std::ostream& os, type_list_<F, R> t) {
			os << to_string(t);
			return os;
		}

		template<class F> std::ostream& operator<<(std::ostream& os, type_list_<F> t) {
			os << to_string(t);
			return os;
		}
	}

	namespace hlist {
		
		template<typename... A> std::ostream& operator<<(std::ostream& os, hnil_<A...> hn) {
			os << to_string(hn);
			return os;
		}
	}

	namespace placeholders {
		
		template<int N> std::ostream& operator<<(std::ostream& os, placeholder_<int_<N>> p) {
			os << to_string(p);
			return os;
		}
	}

	namespace math {
		namespace ratio {
			
			template<class N, class D> std::ostream& operator<<(std::ostream& os, ratio_<N, D> r) {
				os << to_string(r);
				return os;
			}
		}
	}
}

#endif
