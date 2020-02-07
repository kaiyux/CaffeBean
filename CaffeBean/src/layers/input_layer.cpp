//
// Created by Kaiyu Xie on 2020/2/4.
//

#include "../../include/layers/input_layer.h"

InputLayer::InputLayer(const std::string &name) : Layer(name) {
    std::cout << "creating FullyConnectedLayer: " << name << " ..." << std::endl;
}

InputLayer::~InputLayer() {
    std::cout << "layer " << name_ << " deleted" << std::endl;
    delete top_;
    delete bottom_;
}

void InputLayer::init_layer() {}

Bean *InputLayer::forward(Bean *bottom) {
    std::cout << name_ << " forward" << std::endl;
    return top_;
}

Bean *InputLayer::backward(Bean *top) {
    std::cout << name_ << " backward" << std::endl;
    return bottom_;
}

void InputLayer::random_init(std::vector<int> &shape) {
    top_ = new Bean(shape);
    normal(top_);
}
