#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <memory>

# include "../Utils/Utils.hpp"
# include "../Utils/Iterators.hpp"

# include <stddef.h>

namespace ft {

    template<typename T, class Allocator = std::allocator<T> >
    class Vector
    {
        public:
        typedef  T          value_type;

        typedef  Allocator  allocator_type;
        typedef  typename allocator_type::reference  reference;
        typedef  typename allocator_type::const_reference  const_reference;
        typedef  typename allocator_type::pointer  pointer;
        typedef  typename allocator_type::const_pointer  const_pointer;

        typedef  typename ft::RandomAccessIterator<value_type>  iterator;
        typedef  typename ft::iterator_traits<iterator>::difference_type  difference_type;

        typedef  typename ft::reverse_iterator<iterator>  reverse_iterator;

        typedef  typename ft::RandomAccessIterator<const value_type>  const_iterator;
        typedef  typename ft::reverse_iterator<const_iterator>  const_reverse_iterator;

        typedef size_t     size_type;

        private:
            Allocator alloc;
            size_t s;
            size_type cap;

            pointer content;


            void initCapacity(size_t size)
            {

                cap = size;
                // cap = 2;
                // while (cap <= size)
                //     cap *= 2;
            }

        public:

            Vector() : s(0)
            {
                initCapacity(s);
                content = alloc.allocate(s);
            }

            Vector(size_t _size, T val = T()) : s(_size)
            {
                initCapacity(s);
                content = alloc.allocate(cap);
                for (size_t i = 0; i < s; i++)
                    alloc.construct(content + i, val);
            }

            template <class InputIterator>
            Vector (InputIterator first, InputIterator last,
                 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                difference_type size = last - first;
                if(size < 0)
                    return;
                s = size;
                initCapacity(s);
                content = alloc.allocate(cap);
                for (size_t i = 0; i < s; i++)
                {
                    alloc.construct(content + i, *first);
                    first++;
                }
            };

            Vector( Vector const & src ) : s(src.size())
            {
                initCapacity(s);
                content = alloc.allocate(cap);
                for (size_t i = 0; i < s; i++)
                    alloc.construct(content + i, src.at(i));
            };

            ~Vector(){
                alloc.deallocate(content, s);
            };

            Vector &		operator=( Vector const & rhs ){
                assign(rhs.begin(),rhs.end());
                return *this;
            }

            // Element Access
            T &     at(size_t idx) const { 
                if(idx < 0 || idx > size() - 1)
                    throw std::out_of_range("ee");
                return (content[idx]); 
            }
            T &     operator[](size_t idx) const { return content[idx]; }
            T &     front() const { return (content[0]); }
            T &     back() const { return (content[size() - 1]);}
            T       *data() const { return (content); } // cpp11

            // Iterators

            iterator begin(void) const{
                return iterator(content);
            }
            iterator end(void) const{
                return iterator(content + size());
            }
            reverse_iterator rbegin(void) const{
                return reverse_iterator(end());
            }
            reverse_iterator rend(void) const{
                return reverse_iterator(begin());
            }

            // Capacity
            size_t  size()      const { return s; }
            size_t  capacity()  const { return cap; }
            size_t  max_size()  const { return alloc.max_size(); }
            bool    empty()     const { return s == 0; }

            void    resize(size_t _size, T val = T()) {
                if (_size > s)
                {
                    if (_size <= cap)
                    {
                        for (size_t i = s; i < _size; i++)
                            alloc.construct(content + i, val);
                        s = _size;
                    }
                    else
                    {
                        size_t old_cap = cap;
                        initCapacity(_size);
                        T *tmp = alloc.allocate(cap);
                        for (size_t i = 0; i < s; i++)
                        {
                            alloc.construct(tmp + i, content[i]);
                            alloc.destroy(content + i);
                        }
                        alloc.deallocate(content, old_cap);
                        content = tmp;
                        resize(_size, val);
                    }
                }
                else
                {
                    for (size_t i = _size; i < s; i++)
                        alloc.destroy(content + i);
                    s = _size;
                }
            }

            void    reserve(size_t new_cap){
                if(new_cap > max_size())
                    throw std::length_error("3");
                if (new_cap > cap)
                {
                    T *tmp = alloc.allocate(new_cap);
                    size_t old_cap = cap;
                    cap = new_cap;
                    for (size_t i = 0; i < s; i++)
                    {
                        alloc.construct(tmp + i, content[i]);
                        alloc.destroy(content + i);
                    }
                    if(old_cap)
                        alloc.deallocate(content, old_cap);
                    content = tmp;
                }
            }

            // Modifiers
            void clear()
            {
                resize(0);
            }

            void push_back(const T& val)
            {   if(s == 0)
                    reserve(1);
                else if (s+1 > cap)
                    reserve(cap*2);
                alloc.construct(content + s, val);
                s++;
            }

            void pop_back()
            {
                resize(size() - 1);
            }

            template <class InputIterator>
                void assign (InputIterator first, InputIterator last, 
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                clear();
                ptrdiff_t size = last - first;
                if (size < 0)
                    return ;
                resize(size);
                for (size_t i = 0; i < size; i++)
                    alloc.construct(content + i, *(first + i));
            }

            void assign (size_t n, const T& val)
            {
                clear();
                resize(n, val);
            }

            iterator insert (iterator position, const value_type& val)
            {
                difference_type idx = position - begin();
                if(s == 0)
                    reserve(1);
                else if(s + 1 > cap)
                    reserve(cap*2);
                for(size_t rit = s - 1; rit != idx - 1; rit--)
                    content[rit + 1] = content[rit];
                content[idx]=val;
                s++;
                return (begin() + idx);
            }
            
            void insert (iterator position, size_type n, const value_type& val){
             difference_type idx = position - begin();
                if(s == 0)
                    reserve(n);
                else if(cap < s + n && s+n<=cap*2 )
                    reserve(cap*2);
                else reserve(s+n);
                for(size_t rit = s - 1; rit != idx - 1; rit--)
                    content[rit+n] = content[rit];
                for(size_t i = idx; i != idx + n; i++)
                    content[i]=val;
                s+=n;
            }
            
            template <class InputIterator>
                void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
                {
                    difference_type idx = position - begin();
                    difference_type n = last - first;
                    if(s == 0)
                        reserve(n);
                    else if(cap < s + n && s+n<=cap*2 )
                        reserve(cap*2);
                    else reserve(s+n);
                    for(size_t rit = s - 1; rit != idx - 1; rit--)
                        content[rit+n] = content[rit];
                    for(size_t i = idx; i != idx + n; i++)
                        content[i]=*(first++);
                    s+=n;
                }
            
            iterator erase (iterator position){
                difference_type idx = position - begin();
                for(size_t i = idx; i != s - 1; i++)
                    content[i] = content[i+1];
                s--;
                return (begin()+idx);
            }
            iterator erase (iterator first, iterator last)
            {
                difference_type idx = first - begin();
                difference_type n = last - first;

                for(size_t i = idx; i != s - 1; i++)
                    if(i+n < s)
                    content[i] = content[i+n];
                s-=n;
                return (begin() + idx);
            }

            void setAttr(size_type size, size_type capa, pointer cont)
            {
                s = size;
                cap = capa;
                content = cont;
            }

            void swap (Vector& x){
                size_type ss = x.size();
                size_type cc = x.capacity();
                pointer coco = x.data();
                x.setAttr(s, cap, content);
                setAttr(ss,cc,coco);
                //ft::swap(*this, x);
            }

            // Allocator
            Allocator get_allocator() const { return alloc; }

            //operators 
            bool operator== ( const Vector<value_type,allocator_type>& rhs){
                if(s != rhs.size())
                    return false;
                return ft::equal(begin(),end(),rhs.begin());
            }

            bool operator!= ( const Vector<value_type,allocator_type>& rhs){
                return !operator==(rhs);
            }
            

            bool operator<  ( const Vector<value_type,allocator_type>& rhs)
            {
                if(s != rhs.size())
                    return s < rhs.size();
                else return ft::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
            }

            bool operator>= ( const Vector<value_type,allocator_type>& rhs){
                return (!operator<(rhs));
            }
            
            bool operator> ( const Vector<value_type,allocator_type>& rhs){
                if(s != rhs.size())
                    return s > rhs.size();
                else return ft::lexicographical_compare(rhs.begin(),rhs.end(), begin(),end());
            }
            bool operator<= ( const Vector<value_type,allocator_type>& rhs){

                return (!operator>(rhs));
            }




    };

// std::ostream &			operator<<( std::ostream & o, Vector const & i );

    template <class T,class Alloc>
    void swap (ft::Vector<T,Alloc>& a, ft::Vector<T,Alloc>& b) {
        a.swap(b);
    }
}
#endif /* ********************************************************** VECTOR_H */