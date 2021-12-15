#ifndef UTILS_HPP
# define UTILS_HPP
#ifdef LINUX
   typedef typename std::ptrdiff_t ptrdiff_t;
#endif


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
    
    //std::lexicographical_compare
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    //std::equal
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2,
                typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1(),
                typename ft::enable_if<!ft::is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2()
                )
    {
        while (first1!=last1) {
            if (!(*first1 == *first2))
            return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, 
                BinaryPredicate pred,
                typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1(),
                typename ft::enable_if<!ft::is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2())
    {
        while (first1!=last1) {
            if (!pred(*first1, *first2))
            return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class T>
    void swap (T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    // std::pair / std::make_pair
    template <class T1, class T2> struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair(): first(first_type()), second(second_type()){

        }

        pair( const T1& x, const T2& y )
        {
            first_type a = x;
            second_type b = y;
            first = a;
            second = b;
        }

        pair( const pair<T1, T2>& p ): first(first_type(p.first)), second(second_type(p.second))
        {

        }        
        template<typename U1, typename U2>
        pair( const pair<U1, U2>& p ): first(first_type(p.first)), second(second_type(p.second))
        {

        }       

        template<typename U1, typename U2>
        pair& operator=( const pair<U1, U2>& p )
        {
            first = first_type(p.first);
            second = second_type(p.second);
        }      
        template<typename U1, typename U2>
        pair& operator=( const std::pair<U1, U2>& p )
        {
            first = first_type(p.first);
            second = second_type(p.second);
        }      
        pair& operator=( const pair& other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }
        bool operator==(const pair& rhs ){
            if (first == rhs.first)
                return second == rhs.second;
            else 
                return first == rhs.first;
        }

        bool operator!=(const pair& rhs ){
            if (first == rhs.first)
                return second != rhs.second;
            else 
                return first != rhs.first;
        }

        bool operator<(const pair& rhs ){
            if (first == rhs.first)
                return second < rhs.second;
            else 
                return first < rhs.first;
        }

        bool operator<=(const pair& rhs ){
            if (first == rhs.first)
                return second <= rhs.second;
            else 
                return first <= rhs.first;
        }

        bool operator>(const pair& rhs ){
            if (first == rhs.first)
                return second > rhs.second;
            else 
                return first > rhs.first;
        }

        bool operator>=(const pair& rhs ){
            if (first == rhs.first)
                return second >= rhs.second;
            else 
                return first >= rhs.first;
        }
    };

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return pair<T1,T2>(x,y);
    }

}

#endif