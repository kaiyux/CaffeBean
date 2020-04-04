//
// Created by Kaiyu Xie on 2020/2/23.
//

#ifndef CAFFEBEAN_CONFIG_H
#define CAFFEBEAN_CONFIG_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../../lib/jsoncpp/include/json/json.h"

class Config {
private:
    std::string name_;
    std::string type_;
    std::vector<std::string> bottoms_;
    std::vector<std::string> tops_;
    Json::Value params_; // TODO: this is not elegant
public:
    void set_name(std::string name);

    std::string get_name();

    void set_type(std::string type);

    std::string get_type();

    void add_bottom(const std::string &bottom);

    std::vector<std::string> get_bottoms();

    void add_top(const std::string &top);

    std::vector<std::string> get_tops();

    void set_params(Json::Value params);

    Json::Value get_params();
};

#endif //CAFFEBEAN_CONFIG_H
