//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../../include/layers/fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(const std::string &name, int in_features, int out_features, bool has_bias)
        : Layer(name) {
    CAFFEBEAN_LOG("creating FullyConnectedLayer: " << name);
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
    CAFFEBEAN_LOG("layer " << name_ << " deleted");
    delete weight_;
    if (has_bias_) {
        delete bias_;
    }
}

void FullyConnectedLayer::init_layer() {
    CAFFEBEAN_LOG("initializing FullyConnectedLayer: " << name_ << " ...");
    normal(weight_);
    if (has_bias_) {
        normal(bias_);
    }
}

std::vector<Bean *> FullyConnectedLayer::forward(std::vector<Bean *> &bottom) {
    CAFFEBEAN_LOG(name_ << " forward");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.back() == in_features_,
                     bottom[0]->shape_.back() << " != " << in_features_);

    // get the shape of top
    std::vector<int> top_shape = bottom[0]->shape_;
    top_shape.pop_back();
    top_shape.push_back(out_features_);
    std::vector<Bean *> top;
    top.push_back(new Bean(top_shape));

    const int bottom_n = bottom[0]->size_ / bottom[0]->shape_.back();
    matrix_multiply(bottom[0]->data_, weight_->data_, top[0]->data_,
                    bottom_n, in_features_, weight_->shape_[0], out_features_);
    if (has_bias_) {
        const int top_n = top[0]->size_ / top[0]->shape_.back();
        matrix_add(top[0]->data_, bias_->data_, top[0]->data_, top_n, out_features_);
    }
    return top;
}

std::vector<Bean *> FullyConnectedLayer::backward(std::vector<Bean *> &top) {
    CAFFEBEAN_LOG(name_ << " backward");
    std::vector<Bean *> bottom;
    return bottom;
}

Bean *FullyConnectedLayer::get_weight() {
    return weight_;
}

Bean *FullyConnectedLayer::get_bias() {
    return bias_;
}


