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
            RandomAccessIterator(RandomAccessIterator<value_type> const & it) : ptr(&(it[0])) {}

            template <class InputIterator>
            RandomAccessIterator(InputIterator it,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(it[0])){}

            ~RandomAccessIterator() {}

            RandomAccessIterator &operator=(RandomAccessIterator<value_type> const & it)
            {
                RandomAccessIterator tmp = it;
                ptr = &(*tmp);
                return *this;
            }

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
            reference operator*() {return *ptr;}
            pointer operator->() {return ptr;}
            reference operator[](size_t idx) const { return ptr[idx]; }
            RandomAccessIterator operator+ (const RandomAccessIterator& rhs)
            {     
                pointer p = ptr + &(*rhs);
                return RandomAccessIterator(p);
            }
            difference_type operator- (const RandomAccessIterator& rhs){
                RandomAccessIterator tmp = rhs;
                difference_type p = ptr - tmp.ptr;
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
        iterator_type iter;
        reverse_iterator() : ptr(NULL){ }
        reverse_iterator(pointer _ptr) : ptr(_ptr){ }

        template<typename T>
        reverse_iterator(reverse_iterator<T> const& it) : ptr(&(it[0])), iter(it){
        }
        template<class InputIterator>
        reverse_iterator(InputIterator it,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(it[0]) - 1), iter(it)
        {
        }

        ~reverse_iterator() {}

        template<typename U>
        reverse_iterator &operator=(reverse_iterator<U> const & it)
        {
            ptr = it.ptr;
            return *this;
        }

        reverse_iterator operator+=(size_t n){
            this->ptr -= n;
            return *this;
        }
        reverse_iterator operator-=(size_t n){
            this->ptr += n;
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
            difference_type p = rhs.ptr - ptr;
            return p;
        }
        reverse_iterator operator+ (int n){ return reverse_iterator(ptr - n); }
        reverse_iterator operator- (int n){ return reverse_iterator(ptr + n); }

        friend reverse_iterator operator+ (int n, const reverse_iterator& rhs){ return reverse_iterator(rhs.ptr - n); }
        friend reverse_iterator operator- (int n, const reverse_iterator& rhs){ return reverse_iterator(rhs.ptr + n); }

        bool operator==(reverse_iterator<iterator_type> rhs) const {
            reverse_iterator tmp = rhs;
             return ptr == &(*tmp); 
             }
        bool operator==(iterator_type rhs) const { 
            iterator_type tmp = rhs + 1;
            return ptr == &(*tmp);
            }

        bool operator!=(reverse_iterator<iterator_type> rhs) const { 
            reverse_iterator tmp = rhs;
            return ptr != rhs.ptr;
        }


        bool operator< (reverse_iterator<iterator_type> rhs){ return this->ptr > rhs.ptr; }
        bool operator> (reverse_iterator<iterator_type> rhs){ return this->ptr < rhs.ptr; }
        bool operator<=(reverse_iterator<iterator_type> rhs){ return this->ptr >= rhs.ptr; }
        bool operator>=(reverse_iterator<iterator_type> rhs){ return this->ptr <= rhs.ptr; }

        reference operator*() {return *ptr;}

        iterator_type base() const {
            
            return iter;
        }
        pointer operator->() {return &(*ptr);}
        reference operator[](size_t idx) const { return *(ptr - idx);}
    };


    // std::pair / std::make_pair
    template <class T1, class T2> struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair(){

        }

        pair( const T1& x, const T2& y ): first(x), second(y){}

        pair( const pair<T1, T2>& p ): first(p.first), second(p.second){}        

        pair& operator=( const pair& other ){
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
    pair<T1,T2> make_pair (T1 x, T2 y){
        return pair<T1,T2>(x,y);
    }
    // my mapiterator : ft::MapIterator
    template <typename T>
    class MapIterator : public iterator<std::bidirectional_iterator_tag, T> {
        public :

        typedef T                                                           value_type;
        typedef ptrdiff_t                                                   difference_type;
        typedef T*                                                          pointer;
        typedef T&                                                          reference;
        typedef typename  
        iterator<std::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
        typedef typename Node
  
            pointer ptr;
            
            MapIterator(){ }
            MapIterator(pointer _ptr) : ptr(_ptr){ }
            MapIterator(MapIterator<value_type> const & it) : ptr(&(it[0])) {}

            template <class InputIterator>
            MapIterator(InputIterator it,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(it[0])){}

            ~MapIterator() {}

            MapIterator &operator=(MapIterator<value_type> const & it)
            {
                MapIterator tmp = it;
                ptr = &(*tmp);
                return *this;
            }

            // MapIterator &operator++() {++ptr;return *this;}

            // MapIterator operator++(int) {
            //     MapIterator tmp(*this);
            //     operator++();
            //     return tmp;
            // }

            // MapIterator &operator--() {--ptr;return *this;}

            // MapIterator operator--(int) {
            //     MapIterator tmp(*this);
            //     operator--();
            //     return tmp;
            // }
            // reference operator*() {return *ptr;}
            // pointer operator->() {return ptr;}
            // reference operator[](size_t idx) const { return ptr[idx]; }
            // MapIterator operator+ (const MapIterator& rhs)
            // {     
            //     pointer p = ptr + &(*rhs);
            //     return MapIterator(p);
            // }
            // difference_type operator- (const MapIterator& rhs){
            //     MapIterator tmp = rhs;
            //     difference_type p = ptr - tmp.ptr;
            //     return p;
            // }
            // MapIterator operator+=(size_t n){
            //     this->ptr += n;
            //     return *this;
            // }
            // MapIterator operator-=(size_t n){
            //     this->ptr -= n;
            //     return *this;
            // }

            // MapIterator operator+ (int n){ return MapIterator(ptr + n); }
            // MapIterator operator- (int n){ return MapIterator(ptr - n); }
            // friend MapIterator operator+ (int n, const MapIterator& rhs){ return MapIterator(rhs.ptr + n); }
            // friend MapIterator operator- (int n, const MapIterator& rhs){ return MapIterator(rhs.ptr - n); }
            // bool operator==(const MapIterator& rhs) const { return ptr == rhs.ptr; }
            // bool operator!=(const MapIterator& rhs) const { return ptr != rhs.ptr; }

            // bool operator< (const MapIterator& rhs){ return this->ptr < rhs.ptr; }
            // bool operator> (const MapIterator& rhs){ return this->ptr > rhs.ptr; }
            // bool operator<=(const MapIterator& rhs){ return this->ptr <= rhs.ptr; }
            // bool operator>=(const MapIterator& rhs){ return this->ptr >= rhs.ptr; }
    };
}

#endif