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
    std::map<int, char> m;
    for (int i = 0; i < 7; i++)
        m.insert(std::make_pair(i, 'A'));

    std::reverse_iterator<std::map<int, char>::iterator> rit(m.end()), rit_1(--m.end());

    ft::reverse_iterator<std::map<int, char>::iterator> my_rit(m.end()), my_rit1(--m.end());
    /*----------------------------------*/

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";

    // EQUAL((rit->first == (rit_1.base()->first)));// && (my_rit->first == my_rit1.base()->first));

    //std::cout << my_rit->first ;//<< " - "

    //my_rit (end)  first == end - 1
    //my_rit1 (end - 1) base().first == end - 1

    std::cout << my_rit->first; //<< " " << my_rit1.base()->first << std::endl;

    // EQUAL((my_rit->first == my_rit1.base()->first));

    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
    //           << "] --------------------]\t\t\033[0m";
    // EQUAL((rit == rit_1) == (my_rit == my_rit1));
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
    //           << "] --------------------]\t\t\033[0m";
    // EQUAL((rit != rit_1) == (my_rit != my_rit1));
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
    //           << "] --------------------]\t\t\033[0m";
    // EQUAL(((my_rit->first == (--m.end())->first) && ((my_rit->first) == ((--m.end())->first))) && ((rit->first == (--m.end())->first) && ((rit->first) == ((--m.end())->first))));

    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
    //           << "] --------------------]\t\t\033[0m";
    // EQUAL((((*my_rit).first == (*(--m.end())).first) && (((*my_rit).first) == ((*(--m.end())).first))) && (((*rit).first == (*(--m.end())).first) && ((*(rit)).first) == ((*(--m.end())).first)));

    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
    //           << "] --------------------]\t\t\033[0m";
    // ++my_rit; // I incremented here to make sure that the object changes
    // ++rit;
    // EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
    //           << "] --------------------]\t\t\033[0m";
    // --my_rit; // I incremented here to make sure that the object changes
    // --rit;
    // EQUAL((my_rit->first == (--my_rit1)->first) && (rit->first == (--rit_1)->first));
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
    //           << "] --------------------]\t\t\033[0m";
    // {
    //     std::reverse_iterator<std::map<int, char>::iterator> tmp(rit++);
    //     ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit++);
    //     EQUAL(tmp->first == (--rit)->first && my_tmp->first == (--my_rit)->first);
    // }
    // std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
    //           << "] --------------------]\t\t\033[0m";
    // {
    //     rit++;
    //     my_rit++;
    //     std::reverse_iterator<std::map<int, char>::iterator> tmp(rit--);
    //     ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit--);
    //     EQUAL(tmp->first == (++rit)->first && my_tmp->first == (++my_rit)->first);
    // }
    return (0);
}
