#include "base.h"

Base::Base()
{

}

void Base::statmem()
{
}

void Base::pub_mem()
{
}

int Base::memfcn()
{
    return 0;
}

void Deriverd::f(const Deriverd& derived_obj)
{
    Base::statmem();
    Deriverd::statmem();
    derived_obj.statmem();
    statmem();
}

int Deriverd::memfcn(int)
{
    return 0;
}


