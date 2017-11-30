#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

//--------------------------------
// c++11 primer v5
//     chapter 11  map,set
// 关联容器 associative-container
//
//      2017-11-30 @wlnetman@gmail.com
//--------------------------------


void chapter11_1()
{
    std::map<std::string, std::size_t> word_count;
    std::string word;
    while( std::cin >> word)
        ++word_count[word];
    for(const auto &w : word_count)
        std::cout << w.first << " occus " << w.second
                  << ( (w.second > 1) ? " times" : " time")
                  << std::endl;

    std::set<std::string> exclude = {"The", "But", "And", "Or", "An", "A",
                                     "the", "but", "and", "or", "an", "a"};
    while (std::cin >> word) {
        if (exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    for(const auto &w : word_count)
        std::cout << w.first << " occus " << w.second
                  << ( (w.second > 1) ? " times" : " time")
                  << std::endl;
}

int main(int argc,char* argv[])
{
    chapter11_1();
    return 0;
}
