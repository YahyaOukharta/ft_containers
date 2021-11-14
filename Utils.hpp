#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

    //enable if
    template <bool, typename T = void>
    struct enable_if{};

    template <typename T>
    struct enable_if<true, T> { typedef T type; };  

    //is_integral
    template< class T >
    struct is_integral{
        static const bool value = false;
    };
    
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
}

// Integral type : bool, char, char16_t, char32_t, wchar_t, short, int, long, long long
#endif