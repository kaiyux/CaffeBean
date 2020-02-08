//
// Created by Kaiyu Xie on 2020/2/4.
//

#include "../../include/layers/input_layer.h"

InputLayer::InputLayer(const std::string &name) : Layer(name) {
    CAFFEBEAN_LOG("creating FullyConnectedLayer: " << name << " ...");
}

InputLayer::~InputLayer() {
    CAFFEBEAN_LOG("layer " << name_ << " deleted");
}

void InputLayer::init_layer() {}

std::vector<Bean *> InputLayer::forward(std::vector<Bean *> bottom) {
    CAFFEBEAN_LOG(name_ << " forward");
    return top_;
}

std::vector<Bean *> InputLayer::backward(std::vector<Bean *> top) {
    CAFFEBEAN_LOG(name_ << " backward");
    return bottom_;
}

void InputLayer::random_init(std::vector<int> &shape) {
    Bean *top = new Bean(shape);
    normal(top);
    top_.push_back(top);
}
