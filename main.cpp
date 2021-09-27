#include "Vector.hpp"

int main()
{
    ft::Vector<int> a(5,42);
    std::cout << a.size() << std::endl;


    ft::Vector<int> b(a);
    for(size_t i = 0; i < b.size();i++)
        std::cout << b.at(i) << std::endl;

    std::cout << std::endl;
    for(size_t i = 0; i < b.size();i++)
        std::cout << b.at(i) << std::endl;

    std::cout << b.max_size() << std::endl;

    return (0);
}