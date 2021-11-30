#include "Vector.hpp"
#include <vector>
#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 150 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}
void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}
int main()
{
    signal(SIGALRM, alarm_handler);

std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v.swap(v1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v(1e6, "string");
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v.swap(ft_v1);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        ft::Vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(50, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }


    // ft::Vector<int> a(5,10);
    // for (ft::Vector<int>::iterator it = a.begin(); it != a.end(); it++){
    //     std::cout << *it << std::endl;
    // }
    // std::cout << std::endl;
    // a.insert(a.begin()+2,4, 7);

    // for (ft::Vector<int>::iterator it = a.begin(); it != a.end(); it++){
    //     std::cout << *it << std::endl;
    // }
    return (0);
}