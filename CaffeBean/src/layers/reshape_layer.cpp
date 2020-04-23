//
// Created by Kaiyu Xie on 2020/4/14.
//

#include "layers/reshape.layer.h"

ReshapeLayer::ReshapeLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {
    CAFFEBEAN_LOG("creating ReshapeLayer: " << config->get_name() << " ...");
    auto params = config->get_params();
    for (const auto &i:params["output_shape"]) {
        output_shape_.push_back(i.asInt());
    }
}

void ReshapeLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing ReshapeLayer: " << name_ << " ...");
    top[0]->reshape(output_shape_);
}

void ReshapeLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    top[0]->data_ = bottom[0]->data_;
}

void ReshapeLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    bottom[0]->diff_ = top[0]->diff_;
}

std::vector<std::shared_ptr<Bean>> ReshapeLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}
