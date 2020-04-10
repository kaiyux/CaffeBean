//
// Created by Kaiyu Xie on 2020/2/29.
//

#include "layers/relu_layer.h"

ReluLayer::ReluLayer(const std::string &name) : Layer(name) {}

ReluLayer::ReluLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {}

void ReluLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing ReluLayer: " << name_ << " ...");
    top[0]->reshape(bottom[0]->shape_);
}

void ReluLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    for (int i = 0; i < bottom[0]->size_; ++i) {
        top[0]->data_[i] = bottom[0]->data_[i] > 0 ? bottom[0]->data_[i] : 0;
    }
}

void ReluLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    for (int i = 0; i < bottom[0]->size_; ++i) {
        bottom[0]->diff_[i] = bottom[0]->data_[i] > 0 ? top[0]->diff_[i] : 0;
    }
}

std::vector<std::shared_ptr<Bean>> ReluLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}
