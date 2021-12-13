#include "AVL.hpp"
namespace ft
{

    // my mapiterator : ft::MapIterator
    template <typename T>
    class MapIterator : public iterator<std::bidirectional_iterator_tag, T>
    {

    public:
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;

        typedef typename ft::Node<value_type> node_type;
        typedef typename ft::Node<value_type> treetype;

        
        node_type *node;

        MapIterator() {}

        MapIterator(node_type *n) : node(n) {}

        MapIterator(MapIterator<value_type> const &it) : node(it.node) {}

        template <class InputIterator>
        MapIterator(InputIterator it,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : node(it.node) {}

        ~MapIterator() {}

        MapIterator &operator=(MapIterator<value_type> const &it)
        {
            MapIterator tmp = it;
            node = tmp.node;
            return *this;
        }

        MapIterator &operator++() {node = node->next(); return *this;}

        MapIterator operator++(int) {
            MapIterator tmp(*this);
            operator++();
            return tmp;
        }

        MapIterator &operator--() {node = node->previous();return *this;}

        MapIterator operator--(int) {
            MapIterator tmp(*this);
            operator--();
            return tmp;
        }

        reference operator*() {return node->getPair();}
        pointer operator->() { return &(node->getPair());}
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
        bool operator==(const MapIterator& rhs) const { return node == rhs.node; }
        bool operator!=(const MapIterator& rhs) const { return node != rhs.node; }

        // bool operator< (const MapIterator& rhs){ return this->ptr < rhs.ptr; }
        // bool operator> (const MapIterator& rhs){ return this->ptr > rhs.ptr; }
        // bool operator<=(const MapIterator& rhs){ return this->ptr <= rhs.ptr; }
        // bool operator>=(const MapIterator& rhs){ return this->ptr >= rhs.ptr; }
    };
}
