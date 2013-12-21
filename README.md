Wrapper for Reference to Array
==========================
[![Build Status](https://travis-ci.org/rhysd/array_view.png?branch=master)](https://travis-ci.org/rhysd/array_view)

References to array are very common in C++ programs.  In good old C programs, references to array are represented as a pointer and its length like `void f(int const* ptr, size_t const len)`.  In C++, references to array are represented using template parameter like `template<size_t N> void f(int (&arr)[N])`.  And C++ has many useful array classes like `std::array`, `std::vector` and so on.  `array_view` can deal all of them with safe and unified way.

```cpp
#include <iostream>
#include "array_view.hpp"

void show_int_array(arv::array_view<int> view)
{
    std::cout << '{';
    if (!view.empty()) {
        auto itr = view.begin();
        auto const end = view.end();
        while (true) {
            std::cout << *itr;
            if (++itr != end) {
                std::cout << ", ";
            } else {
                break;
            }
        }
    }
    std::cout << "}\n";
}

int main()
{
    int good_old_c_array[] = {1, 2, 3, 4};
    std::array<int, 4> array = {{1, 2, 3, 4}};
    std::vector<int> vector = {1, 2, 3, 4};

    // access arrays with safe and unified way
    show_int_array(good_old_c_array);
    show_int_array(array);
    show_int_array(vector);
    show_int_array({1, 2, 3, 4});
    show_int_array({&good_old_c_array[0], 4});

    return 0;
}
```

## Installation

Copy files in `include/` to a directory in include paths.

```
$ cp include/* path/to/include-dir/
```

## More Usage

When you want to use `array_view` explicitly, use `make_view()`.

```cpp
std::vector<int> v = {1, 2, 3};
auto av = arv::make_view(v);
```

If you want to output `array_view`, include `array_view_output.hpp` and just use `<<`.

```cpp
#include "array_view_output.hpp"
std::vector<int> v = {1, 2, 3, 4, 5};
std::cout << arv::make_view(v); // "{1, 2, 3, 4, 5}" is output
```

You can slice `array_view` to make new sub-array references.

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto av = arv::make_view(v);
auto sub_av = av.slice(/*position*/ 2, /*length*/ 2);
std::cout << sub_av; // {3, 4}
auto sub_av2 = av.slice(arv::check_bound, /*position*/ 2, /*length*/ 2); // check boundary and may throw an exception
std::cout << sub_av2; // {3, 4}
```

## Why don't you use `boost::range`?

I use this library in my job.  Just try to feel what I feel.

## License

This library is distributed under [NYSL](http://www.kmonos.net/nysl/index.en.html).

>  A. This software is "Everyone'sWare". It means:
>  Anybody who has this software can use it as if he/she is
>  the author.
>
>  A-1. Freeware. No fee is required.
>  A-2. You can freely redistribute this software.
>  A-3. You can freely modify this software. And the source
>      may be used in any software with no limitation.
>  A-4. When you release a modified version to public, you
>      must publish it with your name.
>
>  B. The author is not responsible for any kind of damages or loss
>  while using or misusing this software, which is distributed
>  "AS IS". No warranty of any kind is expressed or implied.
>  You use AT YOUR OWN RISK.
>
>  C. Copyrighted to (.......)
>
>  D. Above three clauses are applied both to source and binary
>  form of this software.
