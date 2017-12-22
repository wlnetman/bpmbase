#include <iostream>
#include <memory>
#include <array>
#include <utility>
#include <functional>
#include <windows.h>
#include <Winuser.h>

template <typename T>
std::shared_ptr<T> make_shared_arry(std::size_t size)
{
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

class A: public std::enable_shared_from_this<A>
{
public:
    std::shared_ptr<A> GetSelf()
    {
        return shared_from_this();
    }
};

void chapter4_1()
{
    std::shared_ptr<int> p(new int[10], [](int* p) { delete[] p;});

    {
        std::shared_ptr<int> p = make_shared_arry<int>(10);
        std::shared_ptr<char> p2 = make_shared_arry<char>(10);
    }

    {
        std::shared_ptr<A> spy(new A);
        std::shared_ptr<A> p = spy->GetSelf();
    }
}


/*
template <class T, class... Args> inline
typename std::enable_if<!is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
template <class T> inline
typename std::enable_if<is_array<T>::value && extent<T>::value ==0,std::unique_ptr<T>>::type
make_unique(std::size_t size)
{
    typedef typename remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[size]());
}

template <class T, class ... Args>
typename std::enable_if<extent<T>::value != 0, void>::type make_unique(Args&&...) = delete;
*/

struct MyDelete
{
    void operator()(int *p)
    {
        delete p;
    }
};

void chapter4_2()
{
    // unique_ptr
    std::unique_ptr<int> myPtr(new int);
    std::unique_ptr<int, MyDelete> p (new int(1));
}

std::weak_ptr<int> gw;
void f()
{
    if(gw.expired()){
        std::cout<< "gw is expired\n";
    } else {
        auto spt = gw.lock();
        std::cout<< *spt << std::endl;
    }
}

struct AA;
struct BB;
struct AA{
    std::shared_ptr<BB> bptr;
    ~AA(){ std::cout<<"A is deleted!" <<std::endl;}
};
struct BB{
    std::weak_ptr<AA> aptr;
    ~BB(){ std::cout<<"B is deleted!" <<std::endl;}
};

void TestPtr()
{
    {
        std::shared_ptr<AA> ap(new AA);
        std::shared_ptr<BB> bp(new BB);
        ap->bptr = bp;
        bp->aptr = ap;
    }
}

void chapter4_3()
{
    std::shared_ptr<int> sp(new int(10));
    std::weak_ptr<int> wp(sp);
    std::cout<< wp.use_count()<< std::endl;

    // expired
    if(wp.expired())
    {
        std::cout<< "expired" << std::endl;
    }
    else
    {
        std::cout<< "useful" << std::endl;
    }

    // lock
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
        f();
    }
    TestPtr();
}

#define GUARD(P) std::shared_ptr<void> p##p(p, [](void*p){ GetHandle()->Release(p); } );

void chapter4_4()
{
    // 第三方分配内存
    //void *p = GetHandle()->Create();
    //GUARD(p);
}

int main(int argc, char* argv[])
{
    //chapter4_1();
    //chapter4_2();
    chapter4_3();
    //chapter4_4();
    return 0;
}
