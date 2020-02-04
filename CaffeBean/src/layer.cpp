//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/layer.h"


Layer::Layer(std::string name) {
    name_ = name;
}

Layer::~Layer() {
    std::cout << "Layer " << name_ << " deleted" << std::endl;
}

Bean *Layer::get_top() {
    return top_;
}

Bean *Layer::get_bottom() {
    return bottom_;
}


std::string Layer::get_name() {
    return name_;
}
