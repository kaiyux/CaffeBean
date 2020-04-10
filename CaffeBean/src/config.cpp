//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "config.h"

void Config::set_name(std::string name) {
    name_ = name;
}

std::string Config::get_name() {
    return name_;
}

void Config::set_type(std::string type) {
    type_ = type;
}

std::string Config::get_type() {
    return type_;
}

void Config::add_bottom(const std::string &bottom) {
    bottoms_.push_back(bottom);
}

std::vector<std::string> Config::get_bottoms() {
    return bottoms_;
}

void Config::add_top(const std::string &top) {
    tops_.push_back(top);
}

std::vector<std::string> Config::get_tops() {
    return tops_;
}

void Config::set_params(Json::Value params) {
    params_ = std::move(params);
}

Json::Value Config::get_params() {
    return params_;
}
