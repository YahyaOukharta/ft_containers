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
    /*------------ std::reverse_iterator ---------*/
    ft::Map<int, char> m;
    for (int i = 0; i < 1e2; i++)
        m.insert(ft::make_pair(i, 'A'));

    std::cout << "m.end()="<<&(*(m.end()))<< std::endl;
    ft::reverse_iterator<ft::Map<int, char>::iterator> my_rit(m.end());
    std::cout << "reverse_it(m.end())="<<&(*(my_rit))<< std::endl;

    ft::reverse_iterator<ft::Map<int, char>::iterator> ob(my_rit);
    std::cout << "reverse_it(my_rit)="<<&(*(ob))<< std::endl;
    std::cout << "*rit=" << my_rit->first << std::endl;

    // /*----------------------------------*/
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
    //           << "] --------------------]\t\t\033[0m";
    // {
    //     ft::reverse_iterator<std::map<int, char>::iterator> ob(my_rit);
    //     EQUAL(*my_rit == *ob);
    // }
    return (0);
}