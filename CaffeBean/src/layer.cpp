//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/layer.h"

Layer::Layer(std::string name) {
    name_ = name;
}

Layer::~Layer() {}

std::string Layer::get_name() {
    return name_;
}
