//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../../include/layers/fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(const std::string &name, int in_features, int out_features, bool has_bias)
        : Layer(name) {
    std::cout << "creating FullyConnectedLayer: " << name << " ..." << std::endl;
    in_features_ = in_features;
    out_features_ = out_features;
    has_bias_ = has_bias;
    std::vector<int> weight_shape = {in_features_, out_features_};
    weight_ = new Bean(weight_shape);
    if (has_bias_) {
        bias_ = new Bean(weight_shape);
    }
}

FullyConnectedLayer::~FullyConnectedLayer() {
    std::cout << "layer " << name_ << " deleted" << std::endl;
    delete weight_;
    if (has_bias_) {
        delete bias_;
    }
}

void FullyConnectedLayer::init_layer() {
    std::cout << "initializing FullyConnectedLayer: " << name_ << " ..." << std::endl;
    random_init_zero_one(weight_);
    if (has_bias_) {
        random_init_zero_one(bias_);
    }
}

Bean *FullyConnectedLayer::forward(Bean *bottom) {
    std::cout << name_ << " forward" << std::endl;
    bottom_ = bottom;
//    assert(bottom_->shape_.back() == in_features_);
    return top_;
}

Bean *FullyConnectedLayer::backward(Bean *top) {
    std::cout << name_ << " backward" << std::endl;
    return bottom_;
}

Bean *FullyConnectedLayer::get_weight() {
    return weight_;
}

Bean *FullyConnectedLayer::get_bias() {
    return bias_;
}


