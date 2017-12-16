#ifndef BASE_H
#define BASE_H

#include <algorithm>

class Base
{
public:
    Base();
    static void statmem();
    void pub_mem();
    int memfcn();
protected:
    int prot_mem;
private:
    char priv_mem;
};

class Deriverd final: public Base {
    void f(const Deriverd&);
    int memfcn(int);
public:
    //error: C2877: 'Base::priv_mem' is not accessible from  'Base'
    using Base::pub_mem;
protected:
    using Base::prot_mem;
};

struct Pub_Derv : public Base {
    int f() { return prot_mem; }
};

struct Priv_Derv : private Base {
    int f1() const { return prot_mem; }
};

class Sneaky : public Base{
    friend void clobber(Sneaky&);
    friend void clobber(Base&);
    int j;
};

inline void clobber(Sneaky&s) { s.j = s.prot_mem = 0; }
//error: C2248: 'Base::prot_mem': cannot access protected member declared in class 'Base'
//void clobber(Base&b) { b.prot_mem = 0; }
inline void clobber(Base&b) {}

// 友元继承
class Pal {
public:
    //int f(Base b) { return b.prot_mem; }
    //int f2(Sneaky s) { return s.j; }
    //int f3(Sneaky s) { return s.prot_mem; }
};

class D2 : public Pal{
    int mem(Base b)
        { return 0/*b.prot_mem*/; }
};


#endif // BASE_H
