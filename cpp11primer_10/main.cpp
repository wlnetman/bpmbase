#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <numeric>
#include <iterator>

#define varName(x) #x
void printInt(std::vector<int> vec)
{
    std::cout<< varName(vec) << ":[ ";
    // for_each算法
    // lambda表达式
    std::for_each(vec.begin(), vec.end(),
                  [](int val){ std::cout<< "[" << val << "]";});
    std::cout<< " ],count=" << vec.size() << std::endl;
}

void chapter10_1()
{
    int i = 0;
    std::vector<int> vec(100);
    std::fill(vec.begin(), vec.end(), i++);
    printInt(vec);

    int val = 42;
    auto result = std::find(vec.cbegin(), vec.cend(), val);
    if(result != vec.cend())
        std::cout<< *result <<std::endl;

    std::list<std::string> lst = {"Dashi", "Zongli", "Hege"};
    std::string sval = "Dashi";
    auto ret = std::find(lst.cbegin(), lst.cend(), sval);
    std::cout<< (ret==lst.end() ?  "Not find" : "find" ) << std::endl;

}

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void chapter10_2()
{
    std::vector<int> vec(100);
    std::fill(vec.begin(), vec.end(), 7);
    printInt(vec);

    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout<< "sum = " << sum << std::endl;

    std::vector<int> vec2(101);
    bool ret = std::equal(vec.begin(), vec.end(), vec2.begin());
    std::cout<< (ret ? "equal" : "no equal") << std::endl;

    std::vector<int> vec3;
    std::fill_n(std::back_inserter(vec3), 10, 7);
    printInt(vec3);
    auto it = std::back_inserter(vec3);
    *it = 777;
    printInt(vec3);

    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a1)/sizeof(*a1)];
    std::copy(std::begin(a1), std::end(a1), a2);

    std::list<int> ilst;
    ilst.assign(vec.begin(), vec.end());
    std::replace(ilst.begin(), ilst.end(), 7, 77);
    std::replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(vec), 77, 42);
    printInt(vec);

}

std::string make_plural(size_t ctr,const std::string &word, const std::string &ending)
{
  return (ctr==1) ? word : word+ending;
}
// lambda 表达式
// 问题，格式太难理解，很难写的很整齐易懂
void biggies(std::vector<std::string> &words,
             std::vector<std::string>::size_type sz)
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(),
                [](const std::string &a, const std::string &b)
                    { return a.size() < b.size();} );
    auto wc = std::find_if( words.begin(), words.end(),
                            [sz](const std::string &a)
                            { return a.size() >= sz; });
    auto count = words.end() - wc;
    std::cout<< count << " " << make_plural(count , "word", "s")
             << " of length " << sz << " or longer" << std::endl;
    for_each( wc, words.end(),
              [](const std::string &s){ std::cout << s << " ";});
    std::cout<< std::endl;
}

void chapter10_3()
{
    std::vector<std::string> words = {"Dashi", "Zongli", "Hege"};
    biggies(words, words.size());
}

int main(int argc,char* argv[])
{
    //chapter10_1();
    //chapter10_2();
    chapter10_3();
    return 0;
}
