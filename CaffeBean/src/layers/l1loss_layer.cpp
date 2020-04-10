//
// Created by Kaiyu Xie on 2020/2/8.
//

#include "layers/l1loss_layer.h"

L1LossLayer::L1LossLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {
    CAFFEBEAN_LOG("creating L1LossLayer: " << config->get_name());
    auto params = config->get_params();
    if (params["reduction"].isString()) {
        auto reduction = params["reduction"].asString();
        CAFFEBEAN_ASSERT(reduction == "NONE" || reduction == "MEAN" || reduction == "SUM",
                         "reduction should be one of: \"NONE\", \"MEAN\", \"SUM\"");
        reduction_ = reduction;
    } else {
        reduction_ = "MEAN";
    }
}

L1LossLayer::~L1LossLayer() {}

void L1LossLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing L1LossLayer: " << name_ << " ...");
    diff_ = new Bean(bottom[0]->shape_);

    std::vector<int> top_shape;
    if (reduction_ == "NONE") {
        top_shape = bottom[0]->shape_;
    } else {
        top_shape = {1};
    }
    std::shared_ptr<Bean> bean(new Bean(top_shape));
    top.push_back(bean);
}

void L1LossLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_ASSERT(bottom.size() == 2,
                     "There should be 2 input.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_ == bottom[1]->shape_,
                     "The 2 input shape of l1losslayer should be equal.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() >= 2,
                     "The input shape of l1losslayer should be (N,*).");

    const int size = bottom[0]->size_;
    const int N = bottom[0]->shape_[0];

    matrix_sub(bottom[0]->data_, bottom[1]->data_, diff_->data_, N, size / N);
    matrix_abs(diff_->data_, top[0]->data_, N, size / N);

    // if reduction = SUM or MEAN, the result will be a scalar
    if (reduction_ == "SUM" || reduction_ == "MEAN") {
        float res = matrix_sum(top[0]->data_, 1, top[0]->size_);
        if (reduction_ == "MEAN") {
            res /= (float) size;
        }
        top[0]->data_[0] = res;
    }
    top[0]->diff_[0] = 1;
}

void L1LossLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    const int size = diff_->size_;
    const int N = diff_->shape_[0];
    for (int i = 0; i < 2; ++i) {
        const float sign = (i == 0) ? 1 : -1;
        float alpha;
        if (reduction_ == "MEAN") {
            alpha = sign * top[0]->diff_[0] / (float) bottom[i]->size_;
        } else {
            alpha = sign * top[0]->diff_[0];
        }
        matrix_multiply_constant(diff_->data_, bottom[i]->diff_, alpha, N, size / N);
    }
}

std::string L1LossLayer::get_reduction() {
    return reduction_;
}

std::vector<std::shared_ptr<Bean>> L1LossLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}
