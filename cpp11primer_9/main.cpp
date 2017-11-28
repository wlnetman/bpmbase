#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <forward_list>
#include <array>
#include <deque>

// 适配器
#include <stack>
#include <queue>

struct noDefault{
    noDefault(){ i = 0;}
    int i;
    std::vector<int> a;
};

void chapter9_1()
{
    // 顺序容器创建时需要元素有构造函数
    //std::vector<noDefault> v1(10, init);
    std::vector<noDefault> v2(10);
}

void chapter9_2()
{
    std::list<std::string> a = {"dashi", "zongli", "hege"};
    auto it1 = a.begin();
    std::cout<< *it1 <<std::endl;
    auto it2 = a.rbegin();
    std::cout<< *it2 <<std::endl;
    auto it3 = a.cbegin();
    std::cout<< *it3 <<std::endl;
    auto it4 = a.crbegin();
    std::cout<< *it4 <<std::endl;
    std::list<std::string>::const_iterator it5 = a.begin();
    std::cout<< *it5 <<std::endl;

    std::deque<std::string> authList(a.begin(), a.end());
    std::cout<< "deque[0]:"<< *(authList.begin()) << std::endl;

    std::vector<int> ivec(10, -3);
    std::cout<< ivec[3] << std::endl;

    std::queue<std::string> svec({"sss","bbbbb"});
    std::cout<<svec.front() <<std::endl;

    std::array<int,42> f = {42};
    std::array<int,42> f2 = f;
    std::cout<< f.at(23) << std::endl;
    std::cout<< f2.at(0) << std::endl;

    f.swap(f2);
    std::cout<< f.at(0) << std::endl;
    std::cout<< f2.at(23) << std::endl;
    swap(f2, f);
    std::cout<< f.at(0) << std::endl;
    std::cout<< f2.at(23) << std::endl;

    //assign
    std::vector<std::string> vname = {"hege","zongli"};
    std::list<std::string> name = {"wangLIN","Dashi"};
    name.assign(vname.begin(),vname.end());
    std::cout<< name.front() <<std::endl;
}

void printIntContainer(std::list<int> ilist)
{
    for(auto ix = ilist.begin(); ix != ilist.end(); ++ix){
        if(ix == ilist.end())
            std::cout << *(ix);
        else
            std::cout << *(ix) << "-";
    }
    std::cout<< std::endl;
}
void printIntContainer(std::vector<int> ivec)
{
    if(ivec.size() == 0)
        return;

    std::cout<< "[ ";
    for(auto ix = 0; ix < ivec.size(); ++ix){
        std::cout << "["<< ivec[ix] << "] ";
    }
    std::cout<< "] count:" << ivec.size();
    std::cout<< std::endl;
}

void chapter9_3()
{
    std::vector<std::string> container;
    std::string word;
    while (0&& std::cin >> word) {
        container.push_back(word);
    }
    // push_back 不支持 forward_list, array
    word.push_back('+');
    //word.push_back("+"); //error
    std::cout<< word << std::endl;

    std::list<int> ilist;
    for(size_t ix = 0; ix != 10; ++ix)
        ilist.push_front(ix);
    printIntContainer(ilist);

    ilist.insert(ilist.begin(), 1024);
    printIntContainer(ilist);
    // vector的insert很慢
    std::vector<int> ivec;
    ivec.assign(ilist.begin(), ilist.end());
    printIntContainer(ivec);
    ivec.insert(ivec.begin(), 2333);
    printIntContainer(ivec);

    ivec.insert(ivec.end(), ilist.begin(), ilist.end());
    printIntContainer(ivec);

    // insert的返回值可以反复插入
    int i = 0;
    auto iter = ilist.begin();
    while (std::cin >> i) {
        iter = ilist.insert(iter, i);
        printIntContainer(ilist);
    }

    // 新成员emplace ,用类型的构造函数直接构造对象而不是拷贝对象
    ilist.emplace_front(2048);
    printIntContainer(ilist);
    ilist.emplace_back(4096);
    printIntContainer(ilist);
    ilist.emplace(ilist.begin(), 123);
    printIntContainer(ilist);


    // front
    if( !ilist.empty()){
        ilist.front() = 42;
        auto &v = ilist.back();
        v = 111;
        printIntContainer(ilist);
        auto &v2 = ilist.back();
        v2 = 2222;
        printIntContainer(ilist);
    }


    // erase ,记住返回值一定要记住返回值
    while (0&& !ilist.empty()) {
        ilist.pop_front();
        printIntContainer(ilist);
    }

    std::cout<< "Befor erase:" <<std::endl;
    printIntContainer(ilist);
    auto it = ilist.begin();
    while ( it != ilist.end()) {
        if( *it % 2)
            it = ilist.erase(it);
        else
            ++it;
    }
    std::cout<< "After erase:" <<std::endl;
    printIntContainer(ilist);

    ivec.resize(20);
    std::cout<< "size:" << ivec.size() << "cap:" << ivec.capacity() << std::endl;

    ivec.reserve(50);
    std::cout<< "ivec: size: " << ivec.size()
             << "capactity: " << ivec.capacity() <<std::endl;
    while (ivec.size() != ivec.capacity()) {
        ivec.push_back(1);
    }
    std::cout<< "ivec: size: " << ivec.size()
             << "capactity: " << ivec.capacity() <<std::endl;
    printIntContainer(ivec);

    ivec.push_back(2);
    std::cout<< "ivec: size: " << ivec.size()
             << "capactity: " << ivec.capacity() <<std::endl;
    printIntContainer(ivec);
}

void chapter9_5()
{
    const char* cp = "hello wor";
    char noNull[] = {'H', 'i'};
    std::string s1(cp);
    std::cout<< s1 << std::endl;
    std::string s2(noNull);
    std::cout<< s2<< std::endl;
    std::string s3(s1, 6, 6);
    std::cout<< s3<< std::endl;
    std::string sb = s1.substr(0,1);
    std::cout<< sb << std::endl;

    std::string s("C++ Primer"), s11 = s;
    s.insert(s.size(), " 4th ED.");
    s11.append(" 4th ED.");
    std::cout<< "s1:" << s << "s2:" << s11 << std::endl;
    s11.replace(11, 3, "FIFth");
    std::cout<< "s1:" << s << "s2:" << s11 << std::endl;

    double d = stod(std::string("43"));
    std::cout<< d << std::endl;
    std::string ss = "pi = 3.1415926";
    d = stod(ss.substr(ss.find_first_of("+-.0123456789")));
    std::cout<< d << std::endl;
}

void chapter9_6()
{
    std::deque<int> deq = {1,2};
    std::stack<int> stk(deq);

    std::stack<int> intStack;
    for(size_t ix=0; ix != 10; ++ix){
        intStack.push(ix);
    }
    while ( !intStack.empty()) {
        int value = intStack.top();
        intStack.pop();
        std::cout<< value <<std::endl;
    }
}

int main(int argc,char* argv[])
{
    //chapter9_1();
    //chapter9_2();
    //chapter9_3();
    //chapter9_5();
    chapter9_6();
    return 0;
}
