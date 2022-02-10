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
    // std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rbegin and rend methods "
    //           << "] --------------------]\t\t\033[0m";
    // {
    //     /*------------------ std::vectors ---------------------*/
    //     std::vector<std::string> v1(10, "string2");
    //     std::vector<std::string> const v2(10, "string2");
    //     /*-----------------------------------------------------*/
    //     /*------------------ ft::vectors ---------------------*/
    //     ft::Vector<std::string> ft_v1(10, "string2");
    //     ft::Vector<std::string> const ft_v2(10, "string2");
    //     /*----------------------------------------------------*/
    //     /*------------------ strings to store the results ----*/
    //     std::string res, ft_res, c_res, c_ft_res;
    //     /*----------------------------------------------------*/
    //     std::cout << ft_v2.size() << " " << ft_v2.capacity() << std::endl;
    //     for (std::vector<std::string>::const_reverse_iterator rit = v2.rbegin(); rit != v2.rend(); ++rit) // fill c_res from const v1
    //         c_res += *rit;

    //     std::cout << &*ft_v2.rbegin() << std::endl;
    //     //std::cout << *ft_v2.rend() << std::endl;

    //     for (ft::Vector<std::string>::const_reverse_iterator rit = ft_v2.rbegin(); rit != ft_v2.rend(); ++rit) // fill c_ft_res from const ft_v1
    //     {
    //         std::cout << *rit << std::endl;
    //         std::cout << &(*rit) << std::endl;
    //         c_ft_res += *rit;
    //     }

    //     EQUAL(res == ft_res && c_ft_res == c_res);
    // }
    ft::Vector<std::string> const ft_v(10, "string2");
    ft::Vector<std::string>::reverse_iterator rit = ft_v.rbegin();
    ft::Vector<std::string>::const_reverse_iterator crit = ft_v.rbegin();

    while (rit != ft_v.rend()){
        std::cout << &(*rit) << " " << *rit << std::endl;
        rit++;
    }
    std::cout << std::endl;
    while (crit != ft_v.rend()){
        std::cout << &(*crit) << " " << *crit << std::endl;
        crit++;
    }
    //std::cout << &(*rit) << " " << &(*crit) << std::endl;

    return (0);
}