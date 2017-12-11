#include "folder.h"
#include "message.h"

Folder& Folder::operator=(const Folder &rhs)
{
    clearMsg();

    msgs = rhs.msgs;
    return *this;
}

Folder::~Folder()
{
}

void Folder::addMsg(const Message*)
{
}

void Folder::remMsg(const Message*)
{
}

void Folder::clearMsg()
{
    msgs.clear();
}
