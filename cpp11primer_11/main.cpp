#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>

//--------------------------------
// c++11 primer v5
//     chapter 11  map,set
// 关联容器 associative-container
//
//      2017-11-30 @wlnetman@gmail.com
//--------------------------------

// 打印变量名
#define varName(x) #x
void printStrStrMap(std::map<std::string,std::string> &m)
{
    std::cout<< "map: " << varName(m) << std::endl;
    for(const auto &w : m)
        std::cout << "{ " << w.first << ", "
                  << w.second << " }" << std::endl;
}
void printStrSizeMap(std::map<std::string,std::size_t> &m)
{
    std::cout<< "map: " << varName(m) << std::endl;
    for(const auto &w : m)
        std::cout << "{" << w.first << ", "
                  << w.second << "}" << std::endl;
}
void printIntSet(std::set<int> &s)
{
    std::cout<< "set: " << varName(m)
             << ",size = " << s.size() << std::endl;
    auto i = s.cbegin();
    while ( i != s.cend()) {
        std::cout<< *i << ", ";
        ++i;
    }
    std::cout<< std::endl;
}

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

std::pair<std::string, int>
        process(std::vector<std::string> &v)
{
    if(!v.empty())
        return {v.back(), v.back().size()};
        //return make_pair({v.back(), v.back().size()}); //老版本
    else
        return std::pair<std::string, int>();
}
void chapter11_2()
{
    std::map<std::string, std::size_t> word_count;
    printStrSizeMap(word_count);
    std::set<std::string> exclude = {"The", "But", "And", "Or", "An", "A",
                                     "the", "but", "and", "or", "an", "a"};
    std::map<std::string, std::string> authors = {
                                                    {"Joyce", "James"},
                                                    {"Austen", "Jane"},
                                                    {"Dickens", "Charles"}};
    printStrStrMap(authors);

    std::vector<int> ivec;
    for( std::vector<int>::size_type i = 0; i != 10; ++i){
        ivec.push_back(i);
        ivec.push_back(i);
    }
    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> miset(ivec.begin(), ivec.end());
    std::cout << ivec.size() << std::endl;
    std::cout << iset.size() << std::endl;
    std::cout << miset.size() << std::endl;

    std::vector<std::string> fuck = {"FUck"};
    process(fuck);
}

void chapter11_3()
{
    std::set<std::string>::value_type v1;
    std::set<std::string>::key_type v2;
    std::map<std::string, int>::value_type v3;  // pair
    std::map<std::string, int>::key_type v4;
    std::map<std::string, int>::mapped_type v5;

    std::map<std::string, std::size_t> word_count = { std::make_pair("dashi", 30) };
    auto map_it = word_count.begin();
    std::cout<< map_it->first;
    std::cout<< " " << map_it->second;
    //map_it.first = "Cannot set";   // 不能赋值
    ++map_it->second;   //+1

    // set迭代器是const
    std::set<int> iset = {0,1,2,3,4,5,6,7,8,9};
    std::set<int>::iterator set_it = iset.begin();
    if(set_it != iset.end()){
        // *set_it = 42; 不能赋值
        std::cout<< *set_it << std::endl;
    }

    //
    auto map_it2 = word_count.cbegin();
    while (map_it2 != word_count.cend()) {
        std::cout<< map_it2->first << " occurs"
                 << map_it2->second << " times"
                 << std::endl;
        ++map_it2;
    }


    // insert插入操作
    std::vector<int> ivec = {1,2,3};
    std::set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    set2.insert({33,3,3,4,5,5,5,5,612,});
    printIntSet(set2);

    // insert返回值
    //std::map<std::string, std::size_t> word_count;
    std::string word;
    while ( std::cin >> word) {
        auto ret = word_count.insert( {word, 1});
        if( !ret.second )
            ++ret.first->second;   // 值递增
            //++((ret.first)->second);   // 值递增
    }
    printStrSizeMap(word_count);

    std::multimap<std::string, std::string> authors;
    authors.insert({"dashi", "niubi"});
    authors.insert({"dashi", "niubi222"});


    // 删除
    std::string removal_word = "zongli";
    if(word_count.erase(removal_word))
        std::cout<< "oK" << removal_word << "  removed\n";
    else
        std::cout<< "oops: " << removal_word << " Not Found!\n";

    auto cnt = authors.erase("dashi");
    std::cout<< cnt << std::endl;

    // 下标, 不存在的会创建
    word_count["test"] = 2;
    std::cout<< word_count["test"] << std::endl;
    ++word_count["test"];
    std::cout<< word_count["test"] << std::endl;
    //word_count.at("test2"); // 异常

    //访问元素
    std::set<int> iset2 = {0,1,2,3,4,5,6,7,8,9};
    iset2.find(1);
    iset2.find(11);
    iset2.count(1);
    iset2.count(11);

    std::string search_item("Alain de bottom");
    auto entries = authors.count(search_item);
    auto iter = authors.find(search_item);
    while (entries) {
        std::cout<< iter->second << std::endl;
        ++iter;
        --entries;
    }

    for(auto pos4 = authors.equal_range(search_item);
        pos4.first != pos4.second; ++pos4.first)
        std::cout<< pos4.first->second << std::endl;
}


int main(int argc,char* argv[])
{
    //chapter11_1();
    // 关联容器
    //chapter11_2();
    // 关联容器操作
    chapter11_3();
    return 0;
}
