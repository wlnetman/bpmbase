#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <set>

class Folder;
class Message
{
    friend class Folder;
public:
    explicit Message(const std::string &str = ""):
        contents(str) {}
    Message(const Message&);
    Message(Message &&m);
    Message& operator=(const Message&);
    Message& operator=(Message&&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);
    void swap(Message &lhs, Message &rhs);

    void move_Folders(Message *m);

private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
};

#endif // MESSAGE_H
