#include "AVL.hpp"
namespace ft
{

    // my mapiterator : ft::MapIterator
    template <typename T, class Compare>
    class MapIterator : public iterator<std::bidirectional_iterator_tag, T>
    {

    public:
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;

        typedef typename ft::Node<value_type,Compare> node_type;

        node_type *node;
        bool rend,end;
        MapIterator() {}
        
        MapIterator(node_type *n) : node(n) {
     
            rend=0,end=0;
        }

        MapIterator(MapIterator<value_type, Compare> const &it) : node(it.node) {

            rend=it.rend,end=it.end;
        }

        template <class InputIterator>
        MapIterator(InputIterator it,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : node(it.node) {

            rend=it.rend,end=it.end;
        }

        ~MapIterator() {}

        MapIterator &operator=(MapIterator<value_type, Compare> const &it)
        {
            MapIterator tmp = it;
            node = tmp.node;
            rend=tmp.rend;
            end=tmp.end;
            return *this;
        }

        MapIterator &operator++()
        {
            node_type *n = 0;
            if(rend)
                rend = 0;
            else if (!end)
            {
                if (node)
                    n = node->next();
                if(n)
                    node = n;
                else
                    end = 1;
            }
            return *this;
        }

        MapIterator operator++(int)
        {
            MapIterator tmp(*this);
            operator++();
            return tmp;
        }

        MapIterator &operator--()
        {
            node_type *n = 0;
            if(end)
                end=0;
            else if(!rend)
            {
                if(node)
                {
                    n = node->previous();
                
                }
                if(n)
                    node = n;
                else
                    rend = 1; 
            }
            return *this;
        }

        MapIterator operator--(int)
        {
            MapIterator tmp(*this);
            operator--();
            return tmp;
        }

        reference operator*() const { return node->getPair(); }
        pointer operator->()  const { return &(node->getPair()); }
        // reference operator[](size_t idx) const { return node->getPair(); }

        // MapIterator operator+ (const MapIterator& rhs)
        // {
        //     while ()
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

        MapIterator operator+ (int n)
        {
            MapIterator a(*this);
            while (n)
            {
                ++a;
                n--;
            }
            return a; 
        }

        MapIterator operator- (int n)
        { 
            MapIterator a(*this);
            while (n)
            {
                --a;
                n--;
            }
            return a; 
        }
        // friend MapIterator operator+ (int n, const MapIterator& rhs){ return MapIterator(rhs.ptr + n); }
        // friend MapIterator operator- (int n, const MapIterator& rhs){ return MapIterator(rhs.ptr - n); }
        bool operator==(const MapIterator &rhs) const { 
            return (node == rhs.node) && (end == rhs.end && rend==rhs.rend); 
        }
        bool operator!=(const MapIterator &rhs) const { return !operator==(rhs);}

        // bool operator< (const MapIterator& rhs){ return this->ptr < rhs.ptr; }
        // bool operator> (const MapIterator& rhs){ return this->ptr > rhs.ptr; }
        // bool operator<=(const MapIterator& rhs){ return this->ptr <= rhs.ptr; }
        // bool operator>=(const MapIterator& rhs){ return this->ptr >= rhs.ptr; }
    };

    template <class Iterator> class map_reverse_iterator{

        public:

        typedef Iterator                                iterator_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;

        pointer ptr;
        iterator_type iter;
        map_reverse_iterator() : ptr(NULL){ }
        map_reverse_iterator(pointer _ptr) : ptr(_ptr){ }

        template<typename T>
        map_reverse_iterator(map_reverse_iterator<T> const& it) :iter(it){
        }
        template<class InputIterator>
        map_reverse_iterator(InputIterator it,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : iter(it)
        {
        }

        ~map_reverse_iterator() {}

        template<typename U>
        map_reverse_iterator &operator=(map_reverse_iterator<U> const & it)
        {
            iter = it.iter;
            return *this;
        }

        map_reverse_iterator operator+=(size_t n){
            this->iter -= n;
            return *this;
        }
        map_reverse_iterator operator-=(size_t n){
            this->iter += n;
            return *this;
        }

        map_reverse_iterator &operator++() {--iter;return *this;}

        map_reverse_iterator operator++(int) {
            map_reverse_iterator tmp(*this);
            operator++();
            return tmp;
        }

        map_reverse_iterator &operator--() {++iter;return *this;}

        map_reverse_iterator operator--(int) {
            map_reverse_iterator tmp(*this);
            operator--();
            return tmp;
        }

        map_reverse_iterator operator+ (map_reverse_iterator<iterator_type> rhs){ return map_reverse_iterator(iter + rhs.iter); }
        difference_type operator-(map_reverse_iterator<iterator_type> rhs){
            difference_type p = rhs.iter - iter;
            return p;
        }
        map_reverse_iterator operator+ (int n){ return map_reverse_iterator(iter - n); }
        map_reverse_iterator operator- (int n){ return map_reverse_iterator(iter + n); }

        friend map_reverse_iterator operator+ (int n, const map_reverse_iterator& rhs){ return map_reverse_iterator(rhs.iter - n); }
        friend map_reverse_iterator operator- (int n, const map_reverse_iterator& rhs){ return map_reverse_iterator(rhs.iter + n); }

        bool operator==(map_reverse_iterator<iterator_type> rhs) const {
            map_reverse_iterator tmp = rhs;
             return iter == &(*tmp); 
             }
        bool operator==(iterator_type rhs) const { 
            iterator_type tmp = rhs + 1;
            return iter == &(*tmp);
            }

        bool operator!=(map_reverse_iterator<iterator_type> rhs) const { 
            map_reverse_iterator tmp = rhs;
            return iter != rhs.iter;
        }


        bool operator< (map_reverse_iterator<iterator_type> rhs){ return this->iter > rhs.iter; }
        bool operator> (map_reverse_iterator<iterator_type> rhs){ return this->iter < rhs.iter; }
        bool operator<=(map_reverse_iterator<iterator_type> rhs){ return this->iter >= rhs.iter; }
        bool operator>=(map_reverse_iterator<iterator_type> rhs){ return this->iter <= rhs.iter; }

        reference operator*() {return *iter;}

        iterator_type base() const {
            
            return iter;
        }
        pointer operator->() {return &(*iter);}
        reference operator[](size_t idx) const { return *(iter - idx);}
    };
}
