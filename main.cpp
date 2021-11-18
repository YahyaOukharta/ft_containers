#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);

    ft::Vector<int> b(7,21);
    ft::Vector<int>::iterator it = a.begin();
    a.swap(b);
    std::cout << *it << *(b.begin())<< std::endl;

    return (0);
}