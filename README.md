# Midnight

A C++ template metaprogramming library that can be used to perform complex compile-time calculations easily; essentially, if you find yourself using C++ and saying, "you know what, I could use some more templates in my life," this is the library for you.

This library only deals with compile-time facilities and provides very little runtime capabilities; the library is also header-only and requires no external dependencies other than a C++11 compiler (`clang++` or `g++`) with `constexpr` support.

The main.cpp contains various usecases for this library and contains examples of most functions that are used for processing in midnight.

Another plus side of this library: the standard library is completely optional. If `MIDNIGHT_NO_STD` is specified then midnight will require absolutely none of the standard library. However, this means that native printing of types will no longer be supported. For example, if `MIDNIGHT_NO_STD` is not specified, then something like this will be possible:

```c++
...
typedef midnight::core::int_<5> five;
std::cout << five{} << '\n';
...
```

When compiled and run, this will output:

```
...
int_<5>
...
```

However, if `MIDNIGHT_NO_STD` is specified, then instead of:

```c++
...
std::cout << five{} << '\n';
...
```

You will need to explicitly specify the literal value of the type:

```c++
...
std::cout << five::value << '\n';
...
```

Additionally, this also means that you will lose access to printing type lists.

To conclude, here is an example where you can sum all the odd numbers between 1 and 100 (inclusive) at compile-time.

```c++
#include "midnight.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	typedef typename list::range_<I_(1), I_(101)>::type _1_100; // generates a midnight::list::type_list_ of numbers 1 <= x < 101
	typedef typename list::filter_<
					_1_100,
					bind_<divisible_, _1, I_(2), I_(1)>::bind::type
				>::type _1_100_odd; // filters the previous list so that numbers that, when divided by 2, generate a remainder of 1 remain (i.e. odd numbers)
	typedef typename list::reduce_right_<
					I_(0),
					_1_100_odd,
					add_
				>::type _result; // reduces (folds) the previous list from left to right with a starting value of 0 (adds everything in the list)
	std::cout << _result{} << '\n';
	return 0;
}
```

When compiled and run, this will output:

```c++
int_<2500>
```

This program was a just a demonstration to show some of the features of midnight but there are much faster and concise ways of achieving this same result. The fastest way to achieve this result is to use streams:

```c++
#include "midnight.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	typedef typename list::stream_<I_(1), I_(101), I_(2)>::type _1_100_odd;
	typedef typename list::reduce_stream_<I_(0), _1_100_odd, add_>::type _result;
	std::cout << _result{} << '\n';
	return 0;
}
```
On my machine, the first example took around 6 seconds to finish compiling while the second example took around 0.7 seconds to finish compiling. (The reason the second example is faster is: (1) because it isn't processing the same thing twice (generating 1-100 and then filtering it), and (2) streams are lazy, so the entire list isn't evaluated all at once, so the elements of the stream are being computed as its being reduced). Both output the same thing. [As a sidenote: just incrementing by two and skipping filtering on the first example still takes around 2 seconds to compile on my machine].

The most concise way of doing this (in my opinion) is like so:

```c++
#include "midnight.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	std::cout <<
		apply_<vadd_,
				typename list::range_<I_(1), I_(101), I_(2)>::type
			>::type{}
		<< '\n'; // this applies the list generated (1 to 100, incrementing by 2) to the vadd_ template
	return 0;
}
```

This example utilizes the vadd\_ template, which is the variadic version of the add\_ template (which just adds two template classes), and the apply\_ template which passes a list of arguments to a template.

All three examples produce the same output.
