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
                  [](int val){ std::cout << "[" << val << "]";});
    std::cout<< " ],count=" << vec.size() << std::endl;
}
void printInt(std::list<int> lst)
{
    std::cout<< varName(lst) << ":{ ";
    auto beg = lst.begin();
    if(beg != lst.end())
        std::cout<< *beg++;
    std::for_each(beg, lst.end(),
                  [](int val){ std::cout <<  "," << val;});
    std::cout<< " }, count=" << lst.size() << std::endl;
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

void chapter10_4()
{
    // 插入迭代器 流迭代器 反向迭代器 移动迭代器
    std::list<int> lst = {1,2,3,4,5};
    std::list<int> lst2, lst3;

    // 4 3 2 1
    std::copy(lst.cbegin(), lst.cend(), std::front_inserter(lst2));
    std::copy(lst.cbegin(), lst.cend(), std::inserter(lst3, lst3.begin()));
    printInt(lst2);
    printInt(lst3);

    // 流迭代器
    // TODO: cmd第二次调用std::cin会出错
    if(0){
        std::istream_iterator<int> int_it(std::cin);
        std::istream_iterator<int> int_eof;
        //std::ifstream in("afile");
        //std::istream_iterator<std::string> str_it(std::cin);
        std::vector<int> vec;
        while (int_it != int_eof ) {
            vec.push_back(*int_it++);
        }
        printInt(vec);

        std::vector<int> vec2(int_it, int_eof);
        printInt(vec2);
    }
    std::istream_iterator<int> in(std::cin), eof;
    std::cout<< std::accumulate(in, eof, 0) << std::endl;

    {
        std::vector<int> vec;
        std::ostream_iterator<int> out_iter(std::cout, " ");
        for(auto e : vec)
            *out_iter++ = e;
        std::cout<< std::endl;

        // *跟++ 对于std::cout不作任何事情
        std::copy(vec.begin(), vec.end(), out_iter);
        std::cout<< std::endl; // 等同于std::cout.flush();
    }

    // 反向迭代器
    std::vector<int> vec = {0,1,2,3,4,5,6,7,8,9,10};
    for(auto r_iter = vec.crbegin();
             r_iter != vec.crend();
             ++r_iter)
        std::cout<< *r_iter << std::endl;
    std::sort(vec.begin(), vec.end());
    printInt(vec);
    std::sort(vec.rbegin(), vec.rend());
    printInt(vec);

    std::string line = "wanglin,dashi ,zongli";
    auto comma = std::find(line.cbegin(), line.cend(), ',');
    std::cout<< std::string(line.cbegin(), comma) <<std::endl;
    auto rcomma = std::find(line.crbegin(), line.crend(), ',');
    std::cout<< std::string(line.crbegin(), rcomma) <<std::endl;
}

void chapter10_5()
{
    // 泛型算法:
    //     迭代器类别: iterator category
    //      输入，输出，前向、双向，随机
    //      alg(beg, end, ...)
    std::vector<int> vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::unique(vec.begin(), vec.end());
    int val = 0;
    std::find(vec.begin(), vec.end(), val);
    //std::find_if(vec.begin(), vec.end(), pred);
    std::reverse(vec.begin(), vec.end());
    std::remove_if(vec.begin(), vec.end(),
                   [](int i) -> int { return i % 2;});
    printInt(vec);
}

void chapter10_6()
{
    // 特定算法容器
    //  list forward_list 链表机制
    //   独有的sort,merge,remove,reverse,unique
    //       splice
}

int main(int argc,char* argv[])
{
    //chapter10_1();
    //chapter10_2();
    //chapter10_3();
    //chapter10_4();
    chapter10_5();
    chapter10_6();
    return 0;
}
