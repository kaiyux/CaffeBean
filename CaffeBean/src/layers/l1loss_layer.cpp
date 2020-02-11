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
    const int size = bottom[0]->size_;
    const int N = bottom[0]->shape_[0];
    diff_ = new Bean(bottom[0]->shape_);

    matrix_sub(bottom[0]->data_, bottom[1]->data_, diff_->data_, N, size / N);
    matrix_abs(diff_->data_, top_bean->data_, N, size / N);

    // if reduction = SUM or MEAN, the result will be a scalar
    if (reduction_ == SUM || reduction_ == MEAN) {
        float res = matrix_sum(top_bean->data_, N, size / N);
        if (reduction_ == MEAN) {
            res /= (float) size;
        }
        delete top_bean;
        top_bean = new Bean({1});
        top_bean->data_[0] = res;
    }
    top_bean->diff_[0] = 1;
    return {top_bean};
}

std::vector<Bean *> L1LossLayer::backward(std::vector<Bean *> &top) {
    CAFFEBEAN_LOG(name_ << " backward");
    std::vector<Bean *> bottom;
    const int size = diff_->size_;
    const int N = diff_->shape_[0];
    for (int i = 0; i < 2; ++i) {
        Bean *bottom_bean = new Bean(diff_->shape_);
        bottom.push_back(bottom_bean);
        const float sign = (i == 0) ? 1 : -1;
        float alpha;
        if (reduction_ == MEAN) {
            alpha = sign * top[0]->diff_[0] / (float) bottom[i]->size_;
        } else {
            alpha = sign * top[0]->diff_[0];
        }
        matrix_multiply_constant(diff_->data_, bottom[i]->diff_, alpha, N, size / N);
    }
    return bottom;
}

int L1LossLayer::get_reduction() {
    return reduction_;
}



