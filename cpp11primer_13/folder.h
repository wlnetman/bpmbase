#ifndef FOLDER_H
#define FOLDER_H

#include <set>
#include <string>

class Message;
class Folder
{
    friend class Message;
public:
    explicit Folder(const std::string str = ""):
        contents(str){}
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();

    void addMsg(const Message*);
    void remMsg(const Message*);
    void clearMsg();

private:
    std::string contents;
    std::set<Message*> msgs;
};

#endif // FOLDER_H
