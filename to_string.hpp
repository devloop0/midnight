#if !defined(MIDNIGHT_TO_STRING_HPP) && !defined(MIDNIGHT_NO_STD)
#define MIDNIGHT_TO_STRING_HPP

#include <string>
#include "core_types.hpp"
#include "type_list.hpp"
#include "htype_list.hpp"
#include "placeholders.hpp"
#include "ratio.hpp"

using std::string;
using namespace midnight::core;
using namespace midnight::hlist;
using namespace midnight::list;
using namespace midnight::placeholders;
using namespace midnight::math::ratio;

namespace midnight {
	namespace interop {

		template<int N> string to_string(int_<N>) {
			return "int_<" + std::to_string(N) + ">";
		}
		
		template<bool B> string to_string(bool_<B>) {
			return "bool_<" + string(B ? "true" : "false") + ">";
		}

		template<char C> string to_string(char_<C>) {
			return string("char_<'") + C + "'>";
		}

		template<unsigned int S> string to_string(size_t_<S>) {
			return "size_t_<" + std::to_string(S) + ">";
		}

		string to_string(void_) {
			return "void_";
		}

		string to_string(nil_) {
			return "nil_";
		}

		string to_string_type_list_helper(nil_) {
			return "";
		}

		template<int N> string to_string(placeholder_<int_<N>>) {
			return "_" + std::to_string(N);
		}

		template<typename... A> string to_string(hnil_<A...>) {
			return "hnil_";
		}

		template<class N, class D> string to_string(ratio_<N, D>) {
			return to_string(N{}) + " / " + to_string(D{});
		}

		template<class F, class R> string to_string_type_list_helper(type_list_<F, R>);
		template<class F> string to_string_type_list_helper(type_list_<F>);
		template<class F, class R> string to_string(type_list_<F, R>);
		template<class F> string to_string(type_list_<F>);

		template<class F, class R> string to_string_type_list_helper(type_list_<F, R>) {
			return to_string(F{}) + " " + to_string_type_list_helper(R{});
		}

		template<class F> string to_string_type_list_helper(type_list_<F>) {
			return to_string(F{});
		}
		
		template<class F, class R> string to_string(type_list_<F, R> t) {
			string s = to_string_type_list_helper(t);
			int first = s.find_first_not_of(' '), last = s.find_last_not_of(' ');
			return "[ " + s.substr(first, last - first + 1) + " ]";
		}

		template<class F> string to_string(type_list_<F> t) {
			return "[ " + to_string_type_list_helper(t) + " ]";
		}
	}
}

#endif
