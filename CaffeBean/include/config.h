//
// Created by Kaiyu Xie on 2020/2/23.
//

#ifndef CAFFEBEAN_CONFIG_H
#define CAFFEBEAN_CONFIG_H

#include <string>
#include <vector>

class Config {
private:
    std::string name_;
    std::string type_;
    std::vector<std::string> bottoms_;
    std::vector<std::string> tops_;
public:
    void set_name(std::string name);

    std::string get_name();

    void set_type(std::string type);

    void add_bottom(std::string bottom);

    void add_top(std::string top);
};

#endif //CAFFEBEAN_CONFIG_H
