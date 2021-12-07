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

# define RANGE 10
int rando(){
    static std::vector<int> visited;
    int range = RANGE;
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

    std::srand(unsigned(std::time(0)));
    ft::Vector<int> vec(RANGE);
    std::generate(vec.begin(), vec.end(), rando);

    // for(size_t i = 0; i < vec.size(); i++)
    //     vec[i] = i+1;
    // std::cout << std::endl;

    ft::BST<int> tree(vec);


    tree.print();
    tree.inOrderPrint();

    // ft::Node<int> *s=tree.searchFor(4);
    // if(s)
    // {
    //     std::cout << s->getContent()<< " " << "" << std::endl;
    //     ft::Node<int> *l = tree.getLowestChild(s);
    //     if (l)
    //         std::cout << l->getContent()<< " " << "" << std::endl;
    //     l = tree.getLargestChild(s);
    //     if (l)
    //         std::cout << l->getContent()<< " " << "" << std::endl;

    // }
    // else
    //     std::cout <<  "Found nothing" << std::endl;

    for(size_t i = 0; i < vec.size(); i++)
    {
        tree.deleteWithKey(vec[i]);
        tree.print();
        tree.inOrderPrint();
        std::cout << std::endl;
    }
    return (0);
}