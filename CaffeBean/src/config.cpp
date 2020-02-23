//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "../include/config.h"

void Config::set_name(std::string name) {
    name_ = name;
}

std::string Config::get_name() {
    return name_;
}

void Config::set_type(std::string type) {
    type_ = type;
}

void Config::add_bottom(std::string bottom) {
    bottoms_.push_back(bottom);
}

void Config::add_top(std::string top) {
    tops_.push_back(top);
}
