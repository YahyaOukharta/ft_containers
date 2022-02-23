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
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))



int main()
{
    ft::Map<int, std::string> m;
    for (int i = 0; i < 10; ++i){
        m.insert(ft::make_pair(i,std::string(std::to_string(i))));
        m.print();
        std::cout << std::endl;
    }
    m.print();
    return (0);
}
