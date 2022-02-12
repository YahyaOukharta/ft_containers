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


            difference_type operator- (const RandomAccessIterator& rhs){
                RandomAccessIterator tmp = rhs;
                difference_type p = ptr - tmp.ptr;
                return p;
            }
            RandomAccessIterator operator+=(int n){
                this->ptr += n;
                return *this;
            }
            RandomAccessIterator operator-=(int n){
                this->ptr -= n;
                return *this;
            }

            RandomAccessIterator operator+ (int n)const { return RandomAccessIterator(ptr + n); }
            RandomAccessIterator operator- (int n)const { return RandomAccessIterator(ptr - n); }

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

        iterator_type iter;
        reverse_iterator() :iter(iterator_type()){}

        template<typename T>
        reverse_iterator(reverse_iterator<T> const& it) : iter(it.base()){

        }

        template<class InputIterator>
        reverse_iterator(InputIterator it,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : iter(it)
        {

        }

        ~reverse_iterator() {}


        // = 
        template<typename U>
        reverse_iterator &operator=(reverse_iterator<U> const & it)
        {
            iter = it.base();
            return *this;
        }

        // += -=
        reverse_iterator operator+=(size_t n){
            iter -= n;
            return *this;
        }
        reverse_iterator operator-=(size_t n){
            iter += n;
            return *this;
        }

        // ++ --
        reverse_iterator &operator++() {--iter;return *this;}
        
        reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            operator++();
            return tmp;
        }

        reverse_iterator &operator--() {++iter;return *this;}
        reverse_iterator operator--(int) {
            reverse_iterator tmp(*this);
            operator--();
            return tmp;
        }

        reverse_iterator operator+ (reverse_iterator<iterator_type> rhs)
        {
            return reverse_iterator(iter + rhs); 
        }

        difference_type operator- (reverse_iterator<iterator_type> rhs){
            difference_type p = &(*rhs) - &(*(base()-1));
            return p;
        }
        reverse_iterator operator+ (int n) const { return reverse_iterator(iter - n); }
        reverse_iterator operator- (int n) const { return reverse_iterator(iter + n); }


        friend reverse_iterator operator+ (int n, const reverse_iterator& rhs){ return rhs + n; }
        friend reverse_iterator operator- (int n, const reverse_iterator& rhs){ return rhs - n; }


        bool operator== (reverse_iterator<iterator_type> rhs) const {
            return iter == rhs.base();
        }

        bool operator== (iterator_type rhs) const { 
            return iter == rhs;
        }

        bool operator!= (reverse_iterator<iterator_type> rhs) const { 
            return iter != rhs.base();
        }

        bool operator< (reverse_iterator<iterator_type> rhs){ return iter > rhs.base(); }
        bool operator> (reverse_iterator<iterator_type> rhs){ return iter < rhs.base(); }
        bool operator<=(reverse_iterator<iterator_type> rhs){ return iter >= rhs.base(); }
        bool operator>=(reverse_iterator<iterator_type> rhs){ return iter <= rhs.base(); }

        reference operator*() {
            iterator_type it(iter);
            return *(--it);
        }

        iterator_type base() const {
            return iter;
        }
        pointer operator->() {
            iterator_type it(iter);
            return &(*(--it));
            }

        reference operator[](size_t idx) const { 
            iterator_type it(iter);
            return *(--it - idx);
        }
    };
};

#endif
