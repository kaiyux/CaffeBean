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

void InputLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {}

void InputLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG(name_ << " forward");
}

void InputLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG(name_ << " backward");
}

std::vector<std::shared_ptr<Bean>> InputLayer::get_learnable_beans() {
    return {};
}

std::vector<Bean *> InputLayer::random_init(std::vector<int> &shape) {
    std::vector<Bean *> top;
    Bean *top_bean = new Bean(shape);
    normal(top_bean);
    top.push_back(top_bean);
    return top;
}
