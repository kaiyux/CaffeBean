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

std::vector<Bean *> L1LossLayer::forward(std::vector<Bean *> bottom) {
    CAFFEBEAN_LOG(name_ << " forward");
    CAFFEBEAN_ASSERT(bottom.size() == 2,
                     "There should be 2 input.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_ == bottom[1]->shape_,
                     "The 2 input shape of l1losslayer should be equal.");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() >= 2,
                     "The input shape of l1losslayer should be (N,*).");

}

std::vector<Bean *> L1LossLayer::backward(std::vector<Bean *> top) {
    CAFFEBEAN_LOG(name_ << " backward");
}

int L1LossLayer::get_reduction() {
    return reduction_;
}



