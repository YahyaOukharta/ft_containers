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

            //Capacity
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

            //Element Access
            T &     at(size_t idx) const { return (content[idx]); }
            T &     operator[](size_t idx) const { return content[idx]; }
            T &     front() const { return (content[0]); }
            T &     back() const { return (content[size() - 1]);}

            //Modifiers

            //Allocator
            Allocator get_allocator() const { return alloc; }

    };

// std::ostream &			operator<<( std::ostream & o, Vector const & i );

}
#endif /* ********************************************************** VECTOR_H */