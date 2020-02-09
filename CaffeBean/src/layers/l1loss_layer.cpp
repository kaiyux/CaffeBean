//
// Created by Kaiyu Xie on 2020/2/8.
//

#include "../../include/layers/l1loss_layer.h"

L1LossLayer::L1LossLayer(const std::string &name) : Layer(name) {
    reduction_ = MEAN;
}

L1LossLayer::L1LossLayer(const std::string &name, int reduction) : Layer(name) {
    CAFFEBEAN_ASSERT(reduction == NONE || reduction == MEAN || reduction == SUM,
                     "reduction should be one of: none, mean, sum");
    reduction_ = reduction;
}

L1LossLayer::~L1LossLayer() {}

void L1LossLayer::init_layer() {}

std::vector<Bean *> L1LossLayer::forward(std::vector<Bean *> &bottom) {
    CAFFEBEAN_LOG(name_ << " forward");
    CAFFEBEAN_ASSERT(bottom.size() == 2,
                     "There should be 2 input.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_ == bottom[1]->shape_,
                     "The 2 input shape of l1losslayer should be equal.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() >= 2,
                     "The input shape of l1losslayer should be (N,*).");
    Bean *top_bean = new Bean(bottom[0]->shape_);
    const int N = bottom[0]->shape_[0];
    if (reduction_ == NONE) {
        matrix_sub(bottom[0]->data_, bottom[1]->data_, top_bean->data_, N, bottom[0]->size_ / N);
        matrix_abs(top_bean->data_, top_bean->data_, N, bottom[0]->size_ / N);
    } else if (reduction_ == MEAN) {
        matrix_add(bottom[0]->data_, bottom[1]->data_, top_bean->data_, N, bottom[0]->size_ / N);
        matrix_divide_constant(top_bean->data_, top_bean->data_, 2, N, bottom[0]->size_ / N);
    } else {
        matrix_add(bottom[0]->data_, bottom[1]->data_, top_bean->data_, N, bottom[0]->size_ / N);
    }
    return {top_bean};
}

std::vector<Bean *> L1LossLayer::backward(std::vector<Bean *> &top) {
    CAFFEBEAN_LOG(name_ << " backward");
    std::vector<Bean *> bottom;
    return bottom;
}

int L1LossLayer::get_reduction() {
    return reduction_;
}



