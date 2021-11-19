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
    // template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    // bool equal (InputIterator1 first1, InputIterator1 last1,
    //             InputIterator2 first2, 
    //             bool (*pred)(typename InputIterator1::value_type,typename InputIterator2::value_type),
    //             typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1(),
    //             typename ft::enable_if<!ft::is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2())
    // {
    //     while (first1!=last1) {
    //         if (!pred(*first1, *first2))
    //         return false;
    //         ++first1; ++first2;
    //     }
    //     return true;
    // }

    template <class T>
    void swap (T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    //Iterator traits
    template <class Iterator>
    class iterator_traits{
        public:
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T> 
    class iterator_traits<T*>{
        public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class T> 
    class iterator_traits<const T*>{
        public:
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
            
            RandomAccessIterator(){ }
            RandomAccessIterator(pointer _ptr) : ptr(_ptr){ }
            RandomAccessIterator(const RandomAccessIterator<value_type>& it) : ptr(&(it[0])) {}

            template <class InputIterator>
            RandomAccessIterator(InputIterator it,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(it[0])){}

            ~RandomAccessIterator() {}

            RandomAccessIterator &operator++() {++ptr;return *this;}

            RandomAccessIterator operator++(int) {
                RandomAccessIterator tmp(*this);
                operator++();
                return tmp;
            }

            RandomAccessIterator &operator--() {--ptr;return *this;}

            RandomAccessIterator operator--(int) {
                RandomAccessIterator tmp(*this);
                operator--();
                return tmp;
            }
            RandomAccessIterator operator+ (const RandomAccessIterator& rhs)
            {     
                pointer p = ptr + &(*rhs);
                return RandomAccessIterator(p);
            }
            difference_type operator- (const RandomAccessIterator& rhs){
                difference_type p = ptr - rhs.ptr;
                return p;
            }
            RandomAccessIterator operator+=(size_t n){
                this->ptr += n;
                return *this;
            }
            RandomAccessIterator operator-=(size_t n){
                this->ptr -= n;
                return *this;
            }

            RandomAccessIterator operator+ (int n){ return RandomAccessIterator(ptr + n); }
            RandomAccessIterator operator- (int n){ return RandomAccessIterator(ptr - n); }
            friend RandomAccessIterator operator+ (int n, const RandomAccessIterator& rhs){ return RandomAccessIterator(rhs.ptr + n); }
            friend RandomAccessIterator operator- (int n, const RandomAccessIterator& rhs){ return RandomAccessIterator(rhs.ptr - n); }
            bool operator==(const RandomAccessIterator& rhs) const { return ptr == rhs.ptr; }
            bool operator!=(const RandomAccessIterator& rhs) const { return ptr != rhs.ptr; }
            
            reference operator*() {return *ptr;}
            pointer operator->() {return ptr;}
            reference operator[](size_t idx) const { return ptr[idx]; }

            bool operator< (const RandomAccessIterator& rhs){ return this->ptr < rhs.ptr; }
            bool operator> (const RandomAccessIterator& rhs){ return this->ptr > rhs.ptr; }
            bool operator<=(const RandomAccessIterator& rhs){ return this->ptr <= rhs.ptr; }
            bool operator>=(const RandomAccessIterator& rhs){ return this->ptr >= rhs.ptr; }

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
        
        reverse_iterator() : ptr(NULL){ }
        reverse_iterator(pointer _ptr) : ptr(_ptr){ }
        reverse_iterator(const reverse_iterator& it) : ptr(&(it[0])) {}
        template<class InputIterator>
        reverse_iterator(InputIterator it,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(it[0])){}

        ~reverse_iterator() {}


        iterator_type base() const {
            iterator_type it;//
            return it;
        }
        pointer operator->() {return ptr;}
        reference operator[](size_t idx) const { return ptr[idx]; }

        reverse_iterator operator+=(size_t n){
            this->ptr += n;
            return *this;
        }
        reverse_iterator operator-=(size_t n){
            this->ptr -= n;
            return *this;
        }

        reverse_iterator &operator++() {--ptr;return *this;}

        reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            operator++();
            return tmp;
        }

        reverse_iterator &operator--() {++ptr;return *this;}

        reverse_iterator operator--(int) {
            reverse_iterator tmp(*this);
            operator--();
            return tmp;
        }

        reverse_iterator operator+ (reverse_iterator<iterator_type> rhs){ return reverse_iterator(ptr + rhs.ptr); }
        difference_type operator-(reverse_iterator<iterator_type> rhs){
            difference_type p = ptr - rhs.ptr;
            return p;
        }
        reverse_iterator operator+ (int n){ return reverse_iterator(ptr + n); }
        reverse_iterator operator- (int n){ return reverse_iterator(ptr - n); }

        friend reverse_iterator operator+ (int n, const reverse_iterator& rhs){ return reverse_iterator(rhs.ptr - n); }
        friend reverse_iterator operator- (int n, const reverse_iterator& rhs){ return reverse_iterator(rhs.ptr + n); }

        bool operator==(reverse_iterator<iterator_type> rhs) const { return ptr == rhs.ptr; }

        bool operator!=(reverse_iterator<iterator_type> rhs) const { return ptr != rhs.ptr; }

        bool operator< (reverse_iterator<iterator_type> rhs){ return this->ptr < rhs.ptr; }
        bool operator> (reverse_iterator<iterator_type> rhs){ return this->ptr > rhs.ptr; }
        bool operator<=(reverse_iterator<iterator_type> rhs){ return this->ptr <= rhs.ptr; }
        bool operator>=(reverse_iterator<iterator_type> rhs){ return this->ptr >= rhs.ptr; }

        reference operator*() {return *ptr;}
    };
    template<typename T>
    struct BinaryPredicates
    {
        public:
        
            static bool less(T a, T b){ return a < b;}
            static bool greater(T a, T b){ return a > b;}
            static bool lessOrEqual(T a, T b){ return a <= b;}
            static bool greaterOrEqual(T a, T b){ return a >= b;}
            static bool equals(T a, T b){ return a == b;}
            static bool notEquals(T a, T b){ return a != b;}
    };
}

#endif