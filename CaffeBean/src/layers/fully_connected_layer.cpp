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

Bean *FullyConnectedLayer::forward(std::vector<Bean *> bottom) {
    CAFFEBEAN_LOG(name_ << " forward");
    bottom_ = bottom[0];
    CAFFEBEAN_ASSERT(bottom_->shape_.back() == in_features_,
                     bottom_->shape_.back() << " != " << in_features_);

    // get the shape of top
    std::vector<int> top_shape = bottom_->shape_;
    top_shape.pop_back();
    top_shape.push_back(out_features_);
    top_ = new Bean(top_shape);

    const int bottom_n = bottom_->size_ / bottom_->shape_.back();
    matrix_multiply(bottom_->data_, weight_->data_, top_->data_,
                    bottom_n, in_features_, weight_->shape_[0], out_features_);
    if (has_bias_) {
        const int top_n = top_->size_ / top_->shape_.back();
        matrix_add(top_->data_, bias_->data_, top_->data_, top_n, out_features_);
    }
    return top_;
}

Bean *FullyConnectedLayer::backward(std::vector<Bean *> top) {
    CAFFEBEAN_LOG(name_ << " backward");
    return bottom_;
}

Bean *FullyConnectedLayer::get_weight() {
    return weight_;
}

Bean *FullyConnectedLayer::get_bias() {
    return bias_;
}


