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
    weight_ = std::make_shared<Bean>(weight_shape);
    if (has_bias_) {
        std::vector<int> bias_shape = {out_features_};
        bias_ = std::make_shared<Bean>(bias_shape);
    }
}

FullyConnectedLayer::~FullyConnectedLayer() {
    CAFFEBEAN_LOG("layer " << name_ << " deleted");
}

void FullyConnectedLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom,
                                     std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing FullyConnectedLayer: " << name_ << " ...");
    CAFFEBEAN_ASSERT(bottom.size() == 1, get_name() << " bottom shape incorrect.");
    CAFFEBEAN_ASSERT(top.size() == 1, get_name() << " top shape incorrect.");

    std::vector<int> top_shape = bottom[0]->shape_;
    top_shape.back() = out_features_;
    top[0]->reshape(top_shape);

    normal(weight_.get());
    if (has_bias_) {
        zeros(bias_.get());
    }
}

void FullyConnectedLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_ASSERT(bottom[0]->shape_.back() == in_features_,
                     bottom[0]->shape_.back() << " != " << in_features_);

    // top shape (N,*,out_features_)
    std::vector<int> top_shape = bottom[0]->shape_;
    top_shape.pop_back();
    top_shape.push_back(out_features_);

    // Regard bottom shape (N,*,in_features_) as (bottom_n,in_features_)
    const int bottom_n = bottom[0]->size_ / bottom[0]->shape_.back();
    // y = x * weight + bias_multiplier_ * bias
    matrix_multiply(bottom[0]->data_, weight_->data_, top[0]->data_,
                    bottom_n, in_features_, weight_->shape_[0], out_features_);
    if (has_bias_) {
        std::vector<int> bias_multiplier_shape = {bottom_n};
        bias_multiplier_ = std::make_shared<Bean>(bias_multiplier_shape);
        ones(bias_multiplier_.get());

        // tmp_b = bias_multiplier_ * bias
        auto *tmp_b = new float[bottom_n * bias_->size_]();
        matrix_multiply(bias_multiplier_->data_, bias_->data_, tmp_b, bottom_n, 1, 1, bias_->size_);

        const int top_n = top[0]->size_ / top[0]->shape_.back();
        matrix_add(top[0]->data_, tmp_b, top[0]->data_, top_n, out_features_);
    }
}

void FullyConnectedLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom,
                                   std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_ASSERT(top[0]->shape_.back() == out_features_,
                     top[0]->shape_.back() << "!=" << out_features_);

    // Regard top shape (N,*,out_features_) as (top_n,out_features_)
    const int top_n = top[0]->size_ / top[0]->shape_.back();

    // dx = dy * w.T
    auto weight_transpose = new float[weight_->size_]();
    matrix_transpose(weight_->data_, weight_transpose, weight_->shape_[0], weight_->shape_[1]);
    matrix_multiply(top[0]->diff_, weight_transpose, bottom[0]->diff_,
                    top_n, out_features_, weight_->shape_[1], weight_->shape_[0]);

    // dw = x.T * dy
    auto x_transpose = new float[bottom[0]->size_]();
    matrix_transpose(bottom[0]->data_, x_transpose, bottom[0]->size_ / in_features_, in_features_);
    matrix_multiply(x_transpose, top[0]->diff_, weight_->diff_,
                    in_features_, bottom[0]->size_ / in_features_, top_n, out_features_);

    // db = bias_multiplier_.T * dy
    auto bm_transpose = new float[bias_->size_]();
    matrix_transpose(bias_multiplier_->data_, bm_transpose, bias_multiplier_->size_, 1);
    matrix_multiply(bm_transpose, top[0]->diff_, bias_->diff_,
                    1, bottom[0]->size_ / bottom[0]->shape_.back(),
                    bottom[0]->size_ / bottom[0]->shape_.back(), out_features_);
}

Bean *FullyConnectedLayer::get_weight() {
    return weight_.get();
}

Bean *FullyConnectedLayer::get_bias() {
    return bias_.get();
}

std::vector<std::shared_ptr<Bean>> FullyConnectedLayer::get_learnable_beans() {
    return {weight_, bias_};
}


