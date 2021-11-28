#include "Vector.hpp"
#include <vector>
#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 150 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}
int main()
{

    // std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (single element) "
    //           << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            // time_t start, end, diff;
            // // test 1: test with capacity greater than or equal the size + the new element (reallocation must'nt happen)
            // /*------------------ std::vectors ---------------------*/
            // {
            //     std::vector<std::string> v1(1e6, "string2");
            //     v1.reserve(1e6 + 1);
            //     start = get_time();
            //     v1.insert(v1.begin() + 1e5, "string1");
            //     end = get_time();
            //     diff = end - start;
            //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            //     /*------------------ ft::vectors ---------------------*/
            //     ft::Vector<std::string> ft_v1(1e6, "string2");
            //     ft_v1.reserve(1e6 + 1);
            //     ualarm(diff * 1e3, 0);
            //     ft_v1.insert(ft_v1.begin() + 1e5, "string1");
            //     ualarm(0, 0);
            // }
            // /*--------------------------------------------------------------------------------------*/
            // // test 2: test with capacity lesser than the size + the new element (reallocation must happen)
            // /*------------------ std::vectors ---------------------*/
            // {
            //     std::vector<std::string> v1(1e6, "string2");
            //     start = get_time();
            //     v1.insert(v1.begin() + 1e5, "string1");
            //     end = get_time();
            //     diff = end - start;
            //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            //     /*------------------ ft::vectors ---------------------*/
            //     ft::Vector<std::string> ft_v1(1e6, "string2");
            //     ualarm(diff * 1e3, 0);
            //     ft_v1.insert(ft_v1.begin() + 1e5, "string1");
            //     ualarm(0, 0);
            // }
        }
        /*--------------------------------------------------------------------------------------*/
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        ft::Vector<std::string>::iterator ft_it;
        std::vector<std::string>::iterator it;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
            ft_it = ft_v.insert(ft_v.begin(), "hello");
            ft_it->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str)&& (s == ft_s)&& (c == ft_c) && (*ft_it == *it));
        }
        // // insert at the end
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;

            it = v.insert(v.end(), "hello");
            ft_it = ft_v.insert(ft_v.end(), "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        // // /*---------------------------------------------------------------------------------------------------*/
        // // /*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
        // {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(30);
            ft_v.reserve(30);
            valid_it = ft_v.begin();
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
                std::cout << str << std::endl;
                std::cout << ft_str << std::endl;
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
        // }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
   
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            std::cout << c << std::endl;
            std::cout << ft_c << std::endl;

            cond = (cond && (str == ft_str)&& (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
         EQUAL(cond);
    }
    return (0);
}