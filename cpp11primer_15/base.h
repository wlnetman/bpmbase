#ifndef BASE_H
#define BASE_H


class Base
{
public:
    Base();
    static void statmem();
};

class Deriverd final: public Base {
    void f(const Deriverd&);
};

#endif // BASE_H
