//
// Created by Kaiyu Xie on 2020/2/23.
//

#ifndef CAFFEBEAN_CONFIG_H
#define CAFFEBEAN_CONFIG_H

#include <string>
#include <vector>
#include <unordered_map>

class Config {
private:
    std::string name_;
    std::string type_;
    std::vector<std::string> bottoms_;
    std::vector<std::string> tops_;
    std::unordered_map<std::string, int> params_;
public:
    void set_name(std::string name);

    std::string get_name();

    void set_type(std::string type);

    std::string get_type();

    void add_bottom(const std::string &bottom);

    std::vector<std::string> get_bottoms();

    void add_top(const std::string &top);

    std::vector<std::string> get_tops();

    void add_params(std::string param, int value);

    std::unordered_map<std::string, int> get_params();
};

#endif //CAFFEBEAN_CONFIG_H
