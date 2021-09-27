#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <memory>
# define INITIAL_CAPACITY 100

namespace ft {

    template<typename T, class Allocator = std::allocator<T> >
    class Vector
    {
        private:
            Allocator alloc;
            size_t s;
            size_t cap;

            T *content;

        public:

            Vector() : s(0)
            {
                cap = INITIAL_CAPACITY ;
                content = alloc.allocate(cap);
            }

            Vector(size_t _size) : s(_size)
            {
                content = alloc.allocate(s);
            }

            Vector(size_t _size, T val) : s(_size)
            {
                content = alloc.allocate(s);
                for (size_t i = 0; i < s; i++)
                    content[i] = val;
            }

            // template <class InputIterator>
            // Vector (InputIterator first, InputIterator last) : s(last - first)
            // {
                
            // };

            Vector( Vector const & src ) : s(src.size())
            {
                content = alloc.allocate(s);
                for (size_t i = 0; i < s; i++)
                    content[i] = src.at(i);
            };

            ~Vector(){
                alloc.deallocate(content, s);
            };

            // Vector &		operator=( Vector const & rhs );

            //Capacity
            size_t  size() const { return s; }
            size_t  capacity() const { return cap; }
            size_t  max_size() const { return alloc.max_size(); }
            bool    empty() const { return s == 0; }

            //Element Access
            T &     at(size_t idx) const { return (content[idx]); }
            T &     operator[](size_t idx) const { return content[idx]; }
            //Modifiers

            //Allocator
            Allocator get_allocator() const { return alloc; }

    };

// std::ostream &			operator<<( std::ostream & o, Vector const & i );

}
#endif /* ********************************************************** VECTOR_H */