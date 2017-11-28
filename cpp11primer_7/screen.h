#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>

class Screen {

    // Window_mgr 可以访问私有成员
    friend class Window_mgr;
    //friend class Window_mgr::clear();

public:
    typedef std::string::size_type pos;
    //using std::string::size_type = pos;
    Screen() = default;
    Screen(pos ht, pos wd, char c):height(ht), width(wd),
        contents(ht * wd, c){ }
    char get() const
        { return contents[cursor]; } // 隐式内联
    inline char get( pos ht, pos wd) const; // 显式内联
    Screen &move(pos r, pos c);

    void some_member() const;

    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os)
            { do_display(os); return *this;}
    const Screen &display(std::ostream &os) const
            { do_display(os); return *this;}
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    mutable size_t access_ctr;
    void do_display(std::ostream &os) const{ os << contents;}
};

inline
Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}
void Screen::some_member() const
{
    ++access_ctr;
}
inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;
    return *this;
}


class Window_mgr{
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
    ScreenIndex addScreen(const Screen &s);
};

void Window_mgr::clear(ScreenIndex i){
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

#endif
