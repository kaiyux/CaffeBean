//
// Created by Kaiyu Xie on 2020/4/11.
//

#include "layers/softmax_loss_layer.h"

SoftmaxWithLossLayer::SoftmaxWithLossLayer(std::string name) : Layer(name) {}

SoftmaxWithLossLayer::SoftmaxWithLossLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {
    CAFFEBEAN_LOG("creating SoftmaxWithLossLayer: " << config->get_name());
}

void SoftmaxWithLossLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom,
                                      std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing SoftmaxWithLossLayer: " << name_ << " ...");
    std::vector<int> top_shape = {1};
    std::shared_ptr<Bean> bean(new Bean(top_shape));
    top.push_back(bean);
}

void SoftmaxWithLossLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom,
                                   std::vector<std::shared_ptr<Bean>> &top) {
    // Softmax
    float sum_exp = 0;
    for (int i = 0; i < bottom[0]->size_; ++i) {
        sum_exp += exp(bottom[0]->data_[i]);
    }
    prob_ = new float[bottom[0]->size_]();
    for (int i = 0; i < bottom[0]->size_; ++i) {
        prob_[i] += exp(bottom[0]->data_[i]) / sum_exp;
    }

    // Cross Entropy Loss
    auto prob = new float[bottom[0]->size_]();
    for (int i = 0; i < bottom[0]->size_; ++i) {
        prob[i] = log(prob_[i]);
    }
    auto *loss = new float[1]();
    matrix_multiply(bottom[1]->data_, prob, loss, 1, bottom[1]->size_, bottom[0]->size_, 1);
    top[0]->data_[0] = -loss[0];
}

void SoftmaxWithLossLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom,
                                    std::vector<std::shared_ptr<Bean>> &top) {
    for (int i = 0; i < bottom[0]->size_; ++i) {
        if (bottom[1]->data_[i] == 1) {
            bottom[0]->diff_[i] = prob_[i] - 1;
        } else {
            bottom[0]->diff_[i] = prob_[i];
        }
    }
}

std::vector<std::shared_ptr<Bean>> SoftmaxWithLossLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}
