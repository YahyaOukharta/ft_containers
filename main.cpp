#include "Vector.hpp"
#include <vector>
#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}
int main()
{

        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;

        /*---------------------------------------------------------*/
        // test for a vector with capactiy < size + the new element
        for (size_t i = 0; i < 4; ++i)
            v.push_back("st");

        for (size_t i = 0; i < 4; ++i)
            ft_v.push_back("st");

        z3 = v.size();
        c3 = v.capacity();
        ft_z3 = ft_v.size();
        ft_c3 = ft_v.capacity();
        std::cout << s3<< std::endl << ft_s3<< std::endl << z3<< std::endl << ft_z3<< std::endl << c3<< std::endl << ft_c3<< std::endl;
       // EQUAL((s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    return (0);
}