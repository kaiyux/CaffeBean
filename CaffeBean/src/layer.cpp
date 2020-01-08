//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/layer.h"


Layer::Layer(std::string name) {
    set_name(name);
}

Layer::~Layer() {
    std::cout << "Layer " << this->name << " deleted" << std::endl;
}

Bean Layer::get_top() {
    return this->top;
}

Bean Layer::get_bottom() {
    return this->bottom;
}


std::string Layer::get_name() {
    return this->name;
}

void Layer::set_name(std::string name) {
    this->name = name;
}

Bean Layer::forward() {
    return Bean();
}

Bean Layer::backward() {
    return Bean();
}


