#include "./src/Vector/Vector.hpp"
#include "./src/Stack/Stack.hpp"
#include "./src/Map/Map.hpp"

#include <random>
#include <algorithm>

#include <vector>
#include <map>

#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

# define RANGE 13

#include <sstream>

typedef ft::pair<std::string, int> my_pair;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

my_pair rando(){
    static std::vector<int> visited;
    int range = RANGE;
    int res = std::rand() % range;
    if (std::find(visited.begin(),visited.end(),res) == visited.end())
    {
        std::string t = "test";
        visited.push_back(res);
        return ft::make_pair(t + NumberToString(res), res);
    }
    else return rando();
}

int main()
{
// my_pair 
    std::srand(unsigned(std::time(0)));
    ft::Vector<my_pair > vec(RANGE);
    std::generate(vec.begin(), vec.end(), rando);

    // for(size_t i = 0; i < vec.size(); i++)
    //     vec[i] = i+1;
    // std::cout << std::endl;

    // ft::BST<my_pair > tree(vec);
    // tree.insert(ft::make_pair(std::string("new value1"),42));
    // tree.insert(ft::make_pair(std::string("new value2"),42));
    // tree.insert(ft::make_pair(std::string("new value3"),42));

    // tree.print();
    // tree.inOrderPrint();

    ft::Map<std::string, int> m;
    m.insert(vec.begin(),vec.end());
    m.print();
    m.erase(m.begin());
    m.print();


    ft::Map<std::string, int>::iterator it = m.end()--;
    std::cout << it->first << it->second << std::endl;

    // std::map<std::string, int> m2;
    // m2.insert(std::make_pair<>("hello", 3));
    // ft::Node<my_pair> *n = tree.searchFor("test9");    
    // while (n)
    // {
    //     std::cout << n->getKey() << " " << n->getValue() << std::endl;
    //     n = n->previous();
    // }

    return (0);
}