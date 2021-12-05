#include "Vector.hpp"
#include "Stack.hpp"
#include <random>
#include <algorithm>
#include "Map.hpp"
#include <vector>
#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

int rando(){
    static std::vector<int> visited;
    int range = 10;
    int res = std::rand() % range;
    if (std::find(visited.begin(),visited.end(),res)==visited.end())
    {
        visited.push_back(res);
        return res;
    }
    else return rando();
}

int main()
{
    std::srand(unsigned(std::time(nullptr)));
    ft::Vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), rando);

    for(size_t i = 0; i < vec.size(); i++)
        vec[i] = i*10;
    std::cout << std::endl;

    ft::BST<int> tree(vec);
    tree.print();

    return (0);
}