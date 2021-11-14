# Help

```
    class Vector{
        ...
        ...
        ...

        template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<T>::value, T>::type = InputIterator())
        {
            clear();
            size_t size = last - first;
            if (size < 0)
                return ; // // //
            resize(size);
            for (size_t i = 0; i < size; i++)
            {
                alloc.construct(content + i, first + i);
            }
        }

        void assign (size_t n, const T& val)
        {
            clear();
            resize(n, val);
        }
    }
```

```
    //enable if
    template <bool, typename T = void>
    struct enable_if{};

    template <typename T>
    struct enable_if<true, T> { typedef T type; };  

    //is_integral
    template< class T >
    struct is_integral;
    
    template<> struct is_integral <int>                 { static const bool value = true; };
    template<> struct is_integral <unsigned int>        { static const bool value = true; };
    template<> struct is_integral <long>                { static const bool value = true; };
    template<> struct is_integral <unsigned long>       { static const bool value = true; };
    template<> struct is_integral <long long>           { static const bool value = true; };
    template<> struct is_integral <unsigned long long>  { static const bool value = true; };
    template<> struct is_integral <short>               { static const bool value = true; };
    template<> struct is_integral <wchar_t>             { static const bool value = true; };
    template<> struct is_integral <char>                { static const bool value = true; };
    template<> struct is_integral <bool>                { static const bool value = true; };
```

# Main #1

```
#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);

    std::vector<int> b(10,41);

    a.assign(7,5);
    for(size_t i = 0; i < a.size();i++)
        std::cout << a.at(i) << std::endl;

    return (0);
}
```

```
$> clang++ -o a.out -Wall -Wextra -Werror main.cpp 
    In file included from main.cpp:1:
    ./Vector.hpp:149:94: error: failed requirement '!ft::is_integral<int>::value'; 'enable_if' cannot be used to disable this declaration
                    void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<T>::value, T>::type = InputIterator())
                                                                                                ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    main.cpp:5:21: note: in instantiation of template class 'ft::Vector<int, std::__1::allocator<int> >' requested here
        ft::Vector<int> a(5,42);
$>
```

# Main #2

```
#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);

    std::vector<int> b(10,41);

    a.assign(b.begin(),b.end());
    for(size_t i = 0; i < a.size();i++)
        std::cout << a.at(i) << std::endl;

    return (0);
}
```

```
$> clang++ -o a.out -Wall -Wextra -Werror main.cpp 
    In file included from main.cpp:1:
    ./Vector.hpp:149:94: error: failed requirement '!ft::is_integral<int>::value'; 'enable_if' cannot be used to disable this declaration
                    void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<T>::value, T>::type = InputIterator())
                                                                                                ^~~~~~~~~~~~~~~~~~~~~~~~~~~
    main.cpp:5:21: note: in instantiation of template class 'ft::Vector<int, std::__1::allocator<int> >' requested here
        ft::Vector<int> a(5,42);
                        ^
    main.cpp:9:14: error: no viable conversion from 'std::__1::vector<int, std::__1::allocator<int> >::iterator' (aka '__wrap_iter<int *>') to 'size_t' (aka 'unsigned long')
        a.assign(b.begin(),b.end());
                ^~~~~~~~~
    ./Vector.hpp:162:33: note: passing argument to parameter 'n' here
                void assign (size_t n, const T& val)
                                    ^
    2 errors generated.
```