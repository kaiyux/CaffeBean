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
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() == 2,
                     "The shape of SoftmaxWithLossLayer should be [batch_size, num_class]");
    CAFFEBEAN_ASSERT(bottom[0]->shape_ == bottom[1]->shape_,
                     "The shape of 2 beans from bottom should be the same");
    const int batch_size = bottom[0]->shape_[0];
    const int num_class = bottom[0]->shape_[1];
    prob_ = new float[bottom[0]->size_]();

    // Softmax
    for (int bs = 0; bs < batch_size; ++bs) {
        float max_value = -1e9;
        for (int nc = 0; nc < num_class; ++nc) {
            max_value = std::max(bottom[0]->data_[bs * num_class + nc], max_value);
        }
        float sum_exp = 0;
        for (int nc = 0; nc < num_class; ++nc) {
            prob_[bs * num_class + nc] = exp(bottom[0]->data_[bs * num_class + nc] - max_value);
            sum_exp += prob_[bs * num_class + nc];
        }
        for (int nc = 0; nc < num_class; ++nc) {
            prob_[bs * num_class + nc] /= sum_exp;
        }
    }

    // Cross Entropy Loss
    float loss_val = 0;
    auto loss = new float[bottom[0]->size_]();
    for (int i = 0; i < bottom[0]->size_; ++i) {
        loss[i] = -log(prob_[i]);
        if (bottom[1]->data_[i] == 1) {
            loss_val += loss[i];
        }
    }
    top[0]->data_[0] = loss_val;
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
