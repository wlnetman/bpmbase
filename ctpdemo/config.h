#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>

class Config
{
public:
    Config(std::string &file);

    std::string mdUserId,mdBrokerId,mdPassword,mdFront,mdFlowPath;

    std::vector<std::string>    symbols_list;
    std::map<std::string, bool> main_symbols;

private:
    void load(std::string &file);
};

#endif // CONFIG_H
