#include <iostream>
#include "fmt/format.h"

using namespace std;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int chapter3_1_1()
{
    cout << "Enter two number:" << endl;
    int v1,v2;
    cin >> v1 >> v2;
    cout << fmt::format("The sum of v1 {} and v2 {} is {}\n", v1, v2, v1+v2);
    return 0;
}

int chapter3_1_2()
{
    string s1 = "Dashi";
    string s2(10,'D');
    // format 不提示参数个数不匹配就崩溃
    cout << fmt::format("s1={},s2={}\n", s1, s2);
    while (getline(cin,s1)) {
        if(!s1.empty()) {
            cout << "exit to exit\n";
            string::size_type len = s1.size();
            s2 += s1;
            for(auto &c : s2)
                c = toupper(c);
            cout << s2 << "[" << len << "]" << endl;
        }

        if(s1=="exit")
            break;
    }
    return 0;
}

int chapter3_3_1()
{
    vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    cout << fmt::format("vec's len is :{}\n", vec.size());
    for(auto index=vec.cbegin(); index != vec.cend(); index++)
        cout << fmt::format("{},", *index);

    cout << "Input charset Vector(only 1 charset to end):\n";
    vector<string> strVec;
    string tmp;
    while ( cin >> tmp ) {
        if( tmp.size() <= 1 ){
            cout << fmt::format("0x{}\n", char(tmp[0]));
            break;
        }
        strVec.push_back(tmp);
    }
    cout << fmt::format("Vector[len={}]\n", strVec.size());
    decltype(strVec.size()) i = 0;
    for( auto c : strVec){
        cout << "[" << i << "]" << c << endl;
        i++;
    }

    string first = strVec[0];
    for(auto it = first.begin(); it != first.end(); ++it)
        *it = toupper(*it);

    for(auto it = first.cbegin(); it != first.cend(); ++it)
        cout << *it;
    cout << endl;


   return 0;
}

void chapter3_4()
{
    int sought = 33;
    vector<int> text{0,1,2,3,4,5,6,7,8,9,10};
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg)/2;
    while (mid != text.end() && *mid != sought) {
        if(sought < *mid )
            end = mid;
        else
            // 在mid之后找，所以需要+1
            beg = mid + 1;
        mid = beg + (end - beg)/2;
    }
    if( mid == end ){
        cout << "Not find:" << sought << endl;
    } else {
        cout << "Find: " << *mid << endl;
    }
}

void chapter3_5()
{
    unsigned scores[11] = {};
    unsigned grade;
    while (cin>>grade) {
        if (grade == 0)
            break;
        if(grade <= 100)
            // 牛逼的c++
            ++scores[grade/10];
    }
    for(auto i : scores)
        cout << i << " ";
    cout << endl;

}

int chapter3_6()
{
    int ia[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
    size_t cnt = 0;
    for(auto &row : ia)
        for(auto &col : row){
            col = cnt*2;
            cnt++;
        }
    for(const auto &row : ia){
        for(auto col :row)
            cout << col << "     ";
        cout << endl;
    }
    for(auto p = ia; p != ia + 3; ++p){
        for( auto q = *p; q != *p + 4; ++q)
            cout << *q << ' ';
        cout << endl;
    }

    using int_array = int[4];
    typedef int int_array[4];
    for(int_array *p = ia; p != ia + 3; ++p){
        for(int *q = *p; q != *p +4; ++q)
            cout << *q << ' ';
        cout << endl;
    }
    return 0;
}

int main(int argc,char* argv)
{
    //chapter3_1_1();
    //chapter3_1_2();
    //chapter3_3_1();
    //chapter3_4();
    //chapter3_5();
    chapter3_6();
    return 0;
}
