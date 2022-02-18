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

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    {
                if (first1->first != first2->first || first1->second != first2->second)
            return false;}
    return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};
bool testMapConstructors()
{
    bool cond;
    std::map<char, int> first;
    ft::Map<char, int> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    std::map<char, int> copy(first);
    ft::Map<char, int> m_copy(m_first);

    cond = first.size() == m_first.size() && compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    std::map<char, int> second(first.begin(), first.end());
    ft::Map<char, int> m_second(m_first.begin(), m_first.end());

    cond = cond && second.size() == m_second.size() && compareMaps(second.begin(), second.end(), m_second.begin(), m_second.end());
    std::map<char, int> third(second);
    ft::Map<char, int> m_third(m_second);

    cond = cond && third.size() == m_third.size() && compareMaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    std::map<char, int, classcomp> fourth;  // class as Compare
    ft::Map<char, int, classcomp> m_fourth; // class as Compare

    cond = fourth.size() == m_fourth.size() && cond && compareMaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    ft::Map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    cond = fifth.size() == m_fifth.size() && cond && compareMaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    first = std::map<char, int>();
    m_first = ft::Map<char, int>();

    cond = copy.size() == m_copy.size() && cond && compareMaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    return cond;
}

int main()
{
   {
        bool cond(false);
        // erasing all the elements in the map;
        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::Map<int, std::string> ft_m1;
        //     for (size_t i = 0; i < 1e6; i++)
        //     {
        //         m1.insert(std::make_pair(i, "string2"));
        //         ft_m1.insert(ft::make_pair(i, "string2"));
        //     }

        //     start = get_time();
        //     m1.erase(m1.begin(), m1.end());
        //     end = get_time();
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::Maps ---------------------*/
        //     ualarm(diff * 1e3, 0);
        //     ft_m1.erase(ft_m1.begin(), ft_m1.end());
        //     ualarm(0, 0);
        //     /*----------------------------------------------------*/
        // }
        std::map<char, int> m;
        ft::Map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::Map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        // /* ---------- Testing some edge cases ---------- */

        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m2;

        for (size_t i = 0; i < 20; i++)
        {
            m2.insert(std::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string1"));
        }

        std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
        ft::Map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();
        std::cout << it2->first << ft_it2->first << std::endl;

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        m2.erase(it2->first);
        ft_m2.erase(ft_it2->first);

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());
        std::cout << cond << " " << m2.size() << " " << ft_m2.size() << " " <<  compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end()) << std::endl;

        // std::map<int, std::string> m3;
        // ft::Map<int, std::string> ft_m3;
        // std::vector<int> vec;
        // std::vector<int> ft_vec;
        // std::random_device randDev;
        // std::mt19937 generator(randDev());
        // std::uniform_int_distribution<int> distr(0, 1e8);

        // for (size_t i = 0; i < 1e3; i++)
        // {
        //     m3.insert(std::make_pair(i, "string1"));
        //     ft_m3.insert(ft::make_pair(i, "string1"));
        // }

        // for (size_t i = 0; i < 1e3; ++i)
        // {
        //     int n = distr(generator);
        //     int ret1 = m3.erase(n);
        //     int ret2 = ft_m3.erase(n);

        //     if (ret1 != ret2)
        //     {
        //         cond = false;
        //         break;
        //     }
        // }
        // std::cout << cond << " " << m3.size() << " " << ft_m3.size() << " " <<  compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()) << std::endl;

        // std::cout << m3.size() << " " << ft_m3.size() << std::endl;
        // if (!m3.empty())
        // {
        //     m3.erase(m3.begin(), m3.end());
        //     m3.erase(m3.begin(), m3.end());
        // }
        // if (!ft_m3.empty())
        // {
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        // }
        // std::cout << cond << " " << m3.size() << " " << ft_m3.size() << " " <<  compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()) << std::endl;

        // cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

        EQUAL(cond);
    }
    return (0);
}
