#include "Vector.hpp"
#include <vector>
#include <iomanip>
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

int main()
{
           /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> const ft_v2(10, "string2");
        // for (ft::Vector<std::string>::const_reverse_iterator it = ft_v2.rbegin(); it!=ft_v2.rend(); ++it)
        //     std::cout << *it << std::endl;
        ft::Vector<std::string>::const_reverse_iterator it1 = ft_v2.rend();
        ft::Vector<std::string>::reverse_iterator it2 = ft_v2.rend();

        std::cout << it1.ptr << " " << it2.ptr<<std::endl;
    return (0);
}