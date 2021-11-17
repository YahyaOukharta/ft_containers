#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);
    std::cout << a.size()<<std::endl;   
    std::vector<int> b(7,21);

     //a.assign(10,5);
    a.assign(b.begin(), b.end()-5);
    for(ft::Vector<int>::iterator it = a.begin(); it != a.end();it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    a.insert(a.begin() + 2, 8, 12345);
    for(ft::Vector<int>::iterator it = a.begin(); it != a.end();it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    a.erase(a.begin()+3, a.end());
    for(ft::Vector<int>::iterator it = a.begin(); it != a.end();it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    return (0);
}