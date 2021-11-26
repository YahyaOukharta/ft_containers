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

    // std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " push_back method "
    //           << "] --------------------]\t\t\033[0m";
    // {

    //     /*------------------ std::vectors ---------------------*/
    //     std::vector<std::string> v;
    //     /*------------------ std::vectors ---------------------*/
    //     ft::Vector<std::string> ft_v;
    //     /*
    //      * Strings to store the results
    //      */
    //     std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
    //     /*
    //      * Var to store the size and the capacity
    //      */
    //     size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
    //     size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
    //     ft::Vector<std::string>::iterator ft_it;
    //     // test for an empty vector
    //     v.push_back("hello");
    //     ft_v.push_back("hello");
    //     ft_it = ft_v.begin();
    //     ft_it->length();

    //     z1 = v.size();
    //     c1 = v.capacity();
    //     ft_z1 = ft_v.size();
    //     ft_c1 = ft_v.capacity();
    //     for (size_t i = 0; i < v.size(); ++i)
    //         s1 += v.at(i);

    //     for (size_t i = 0; i < ft_v.size(); ++i)
    //         ft_s1 += ft_v.at(i);
    //     /*---------------------------------------------*/
    //     // test for a vector with capacity >= size + the new element
    //     v.reserve(30);
    //     ft_v.reserve(30);
    //     v.push_back("string");
    //     ft_v.push_back("string");
    //     v.push_back("string");
    //     ft_v.push_back("string");

    //     z2 = v.size();
    //     c2 = v.capacity();
    //     ft_z2 = ft_v.size();
    //     ft_c2 = ft_v.capacity();
    //     for (size_t i = 0; i < v.size(); ++i)
    //         s2 += v.at(i);

    //     for (size_t i = 0; i < ft_v.size(); ++i)
    //         ft_s2 += ft_v.at(i);
    //     /*---------------------------------------------------------*/
    //     // test for a vector with capactiy < size + the new element
    //     for (size_t i = 0; i < 100; ++i)
    //         v.push_back("string");

    //     for (size_t i = 0; i < 100; ++i)
    //         ft_v.push_back("string");

    //     z3 = v.size();
    //     c3 = v.capacity();
    //     ft_z3 = ft_v.size();
    //     ft_c3 = ft_v.capacity();
    //     for (size_t i = 0; i < v.size(); ++i)
    //         s3 += v.at(i);

    //     for (size_t i = 0; i < ft_v.size(); ++i)
    //         ft_s3 += ft_v.at(i);

    //     EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    // }
        std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " capacity method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.capacity();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.capacity();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> ft_v2;
        ft::Vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::Vector<std::string> ft_v4(ft_v1);
        ft::Vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/


        EQUAL(v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity() && v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity() && v5.capacity() == ft_v5.capacity());
            std::cout << v1.capacity() << " " << ft_v1.capacity() << std::endl;
            std::cout << v1.capacity() << " " << ft_v1.capacity() << std::endl;
        }
    return (0);
}