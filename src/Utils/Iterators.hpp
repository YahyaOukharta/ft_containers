#ifndef __ITERATORS_HPP__
# define __ITERATORS_HPP__

namespace ft{
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
            RandomAccessIterator(RandomAccessIterator<value_type> const & it) : ptr((it.ptr)) {}

            template <class InputIterator>
            RandomAccessIterator(InputIterator it,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(*it)){}

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
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : ptr(&(*it) - 1), iter(it)
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


};

#endif
