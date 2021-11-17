#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);
    std::cout << a.size()<<std::endl;   
    std::vector<int> b(10,41);

     //a.assign(10,5);
    a.assign(b.begin(), b.end()-5);
    for(ft::Vector<int>::iterator it = a.begin(); it != a.end();it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    a.insert(a.end(), 12345);
    for(ft::Vector<int>::iterator it = a.begin(); it != a.end();it++)
        std::cout << *it << std::endl;
    return (0);
}