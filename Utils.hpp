#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {
    // std::pair / std::make_pair
    template <class T1, class T2> struct pair;

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y);
    
    //std::lexicographical_compare
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2);

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp);

    //std::equal
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2);
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, BinaryPredicate pred);

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

    template <class T>
    void swap (T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    //Iterator traits
    template <class Iterator>
    class iterator_traits{
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T> 
    class iterator_traits<T*>{
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class T> 
    class iterator_traits<const T*>{
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };


    // ft::iterator base class
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    // my iterator : ft::RandomAccessIterator
    template <typename T>
    class RandomAccessIterator : public iterator<std::random_access_iterator_tag, T> {
        public :

        typedef T                                                           value_type;
        typedef ptrdiff_t                                                   difference_type;
        typedef T*                                                          pointer;
        typedef T&                                                          reference;
        typedef typename 
        iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;

  
            pointer ptr;
            
            RandomAccessIterator(pointer _ptr) : ptr(_ptr){ }
            RandomAccessIterator(const RandomAccessIterator& it) : ptr(it.ptr) {}
            ~RandomAccessIterator() {}

            RandomAccessIterator &operator++() {++ptr;return *this;}

            RandomAccessIterator operator++(value_type) {
                RandomAccessIterator tmp(*this);
                operator++();
                return tmp;
            }

            RandomAccessIterator &operator--() {--ptr;return *this;}

            RandomAccessIterator operator--(value_type) {
                RandomAccessIterator tmp(*this);
                operator--();
                return tmp;
            }
            RandomAccessIterator operator+ (const RandomAccessIterator& rhs){ return RandomAccessIterator(ptr + rhs.ptr); }
            RandomAccessIterator operator- (const RandomAccessIterator& rhs){ return RandomAccessIterator(ptr - rhs.ptr); }

            RandomAccessIterator operator+ (int n){ return RandomAccessIterator(ptr + n); }
            RandomAccessIterator operator- (int n){ return RandomAccessIterator(ptr - n); }
            bool operator==(const RandomAccessIterator& rhs) const { return ptr == rhs.ptr; }
            bool operator!=(const RandomAccessIterator& rhs) const { return ptr != rhs.ptr; }
            reference operator*() {return *ptr;}

    };


    template <class Iterator> class reverse_iterator{

        public:

        typedef Iterator                                iterator_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;

        pointer ptr;
        
        reverse_iterator(pointer _ptr) : ptr(_ptr){ }
        reverse_iterator(const reverse_iterator& it) : ptr(it.ptr) {}
        ~reverse_iterator() {}

        reverse_iterator &operator++() {--ptr;return *this;}

        reverse_iterator operator++(value_type) {
            reverse_iterator tmp(*this);
            operator++();
            return tmp;
        }

        reverse_iterator &operator--() {++ptr;return *this;}

        reverse_iterator operator--(value_type) {
            reverse_iterator tmp(*this);
            operator--();
            return tmp;
        }
        

        reverse_iterator operator+ (const iterator_type& rhs){ return reverse_iterator(ptr + rhs.ptr); }
        reverse_iterator operator- (const iterator_type& rhs){ return reverse_iterator(ptr - rhs.ptr); }

        reverse_iterator operator+ (int n){ return reverse_iterator(ptr + n); }
        reverse_iterator operator- (int n){ return reverse_iterator(ptr - n); }


        bool operator==(const iterator_type& rhs) const { return ptr == rhs.ptr; }

        bool operator!=(const iterator_type& rhs) const { return ptr != rhs.ptr; }

        bool operator< (const iterator_type& rhs){ return this->ptr < rhs.ptr; }
        bool operator> (const iterator_type& rhs){ return this->ptr > rhs.ptr; }
        bool operator<=(const iterator_type& rhs){ return this->ptr <= rhs.ptr; }
        bool operator>=(const iterator_type& rhs){ return this->ptr >= rhs.ptr; }

        reference operator*() {return *ptr;}
    };
}

#endif