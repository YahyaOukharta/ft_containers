#include "./src/Vector/Vector.hpp"
#include "./src/Stack/Stack.hpp"
#include "./src/Map/Map.hpp"

#include <random>
#include <algorithm>

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
    if (std::find(visited.begin(),visited.end(),res) == visited.end())
    {
        visited.push_back(res);
        return res;
    }
    else return rando();
}

int main()
{

    // std::srand(unsigned(std::time(0)));
    // ft::Vector<int> vec(RANGE);
    // std::generate(vec.begin(), vec.end(), rando);

    // // for(size_t i = 0; i < vec.size(); i++)
    // //     vec[i] = i+1;
    // // std::cout << std::endl;

    // ft::BST<int> tree(vec);
    
    return (0);
}