#include "Vector.hpp"
#include <vector>
int main()
{
    ft::Vector<int> a(5,42);

    std::vector<int> b(10,41);

    a.assign(b.begin(),b.end());
    for(size_t i = 0; i < a.size();i++)
        std::cout << a.at(i) << std::endl;

    return (0);
}