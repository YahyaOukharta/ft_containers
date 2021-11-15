#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <memory>
# define INITIAL_CAPACITY 100
# include "Utils.hpp"


namespace ft {

    template<typename T, class Allocator = std::allocator<T> >
    class Vector
    {
        //Member Types :
        typedef  T          value_type;

        typedef  Allocator  allocator_type;
        typedef  typename allocator_type::reference  reference;
        typedef  typename allocator_type::const_reference  const_reference;
        typedef  typename allocator_type::pointer  pointer;
        typedef  typename allocator_type::const_pointer  const_pointer;

        // typedef  std::iterator<T,allocator_type>  iterator;
        // typedef  std::const_iterator  const_iterator;///
        // typedef  std::reverse_iterator<iterator>  reverse_iterator;
        // typedef  std::reverse_iterator<const_iterator>  const_reverse_iterator;
        // typedef  std::iterator_traits<iterator>::difference_type  difference_type;

        typedef size_t     size_type;

        private:
            Allocator alloc;
            size_t s;
            size_t cap;

            T *content;


            void initCapacity(size_t size)
            {
                cap = INITIAL_CAPACITY;
                while (cap <= size)
                    cap *= 2;
            }

        public:

            Vector() : s(0)
            {
                initCapacity(s);
                content = alloc.allocate(cap);
            }

            Vector(size_t _size, T val = T()) : s(_size)
            {
                initCapacity(s);
                content = alloc.allocate(cap);
                for (size_t i = 0; i < s; i++)
                    alloc.construct(content + i, val);
            }



            // template <class InputIterator>
            // Vector (InputIterator first, InputIterator last) : s(last - first)
            // {
                
            // };

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

            // Vector &		operator=( Vector const & rhs );

            // Element Access
            T &     at(size_t idx) const { return (content[idx]); }
            T &     operator[](size_t idx) const { return content[idx]; }
            T &     front() const { return (content[0]); }
            T &     back() const { return (content[size() - 1]);}
            T       *data() const { return (content); } //cpp11

            // Iterators

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

            void    reserve(size_t min_capacity){
                if (min_capacity > cap)
                {
                    size_t old_cap = cap;
                    cap = min_capacity;
                    T *tmp = alloc.allocate(cap);
                    for (size_t i = 0; i < s; i++)
                    {
                        alloc.construct(tmp + i, content[i]);
                        alloc.destroy(content + i);
                    }
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
            {
                resize(size() + 1, val);
            }

            void pop_back()
            {
                resize(size() - 1);
            }

            template <class InputIterator>
                void assign (InputIterator first, InputIterator last, 
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                std::cout << "it"<<std::endl;
                clear();
                size_t size = last - first;
                if (size < 0)
                    return ; // // //
                resize(size);
                for (size_t i = 0; i < size; i++)
                {
                    alloc.construct(content + i, *(first + i));
                }
            }

            void assign (size_t n, const T& val)
            {
                std::cout << "val"<<std::endl;
                clear();
                resize(n, val);
            }

            // Allocator
            Allocator get_allocator() const { return alloc; }

    };

// std::ostream &			operator<<( std::ostream & o, Vector const & i );

}
#endif /* ********************************************************** VECTOR_H */