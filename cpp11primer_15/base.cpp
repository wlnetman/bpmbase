#include "base.h"

Base::Base()
{

}

void Deriverd::f(const Deriverd& derived_obj)
{
    Base::statmem();
    Deriverd::statmem();
    derived_obj.statmem();
    statmem();
}

void Base::statmem()
{

}
