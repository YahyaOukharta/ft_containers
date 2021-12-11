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

# define RANGE 13

#include <sstream>

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

ft::pair<int, std::string> rando(){
    static std::vector<int> visited;
    int range = RANGE;
    int res = std::rand() % range;
    if (std::find(visited.begin(),visited.end(),res) == visited.end())
    {
        std::string t = "test";
        visited.push_back(res);
        return ft::make_pair(res, t + NumberToString(res));
    }
    else return rando();
}

int main()
{
// ft::pair<int, std::string> 
    std::srand(unsigned(std::time(0)));
    ft::Vector<ft::pair<int, std::string> > vec(RANGE);
    std::generate(vec.begin(), vec.end(), rando);

    // for(size_t i = 0; i < vec.size(); i++)
    //     vec[i] = i+1;
    // std::cout << std::endl;

    ft::BST<ft::pair<int, std::string> > tree(vec);
    // std::string t = "test";
    // tree.insert(ft::make_pair(10, t));
    tree.print();
    
    return (0);
}