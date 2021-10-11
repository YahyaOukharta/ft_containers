#include "Vector.hpp"

int main()
{
    ft::Vector<int> a(5,42);
    a.reserve(2);
    std::cout << a.capacity() << std::endl;
    std::cout << a.size() << std::endl;

    ft::Vector<int> b(a);
    b.resize(7, 44);
    for(size_t i = 0; i < b.size();i++)
        std::cout << b.at(i) << std::endl;
    b[0] = 999;
    b[b.size() - 1] = -9999;
    std::cout << b.back()<< std::endl;
    // for(size_t i = 0; i < b.size();i++)
    //     std::cout << b.at(i) << std::endl;

    // std::cout << b.max_size() << std::endl;

    return (0);
}