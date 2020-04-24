//
// Created by Kaiyu Xie on 2020/4/23.
//

#include "layers/accuracy_layer.h"

AccuracyLayer::AccuracyLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {}

void AccuracyLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing AccuracyLayer: " << name_ << " ...");
    std::vector<int> top_shape = {1};
    std::shared_ptr<Bean> bean(new Bean(top_shape));
    top.push_back(bean);
}

void AccuracyLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() == 2,
                     "The bottom shape of AccuracyLayer should be [batch_size, num_class]");
    CAFFEBEAN_ASSERT(bottom[0]->shape_ == bottom[1]->shape_,
                     "The shape of 2 beans from bottom should be the same");
    const int batch_size = bottom[0]->shape_[0];
    const int num_class = bottom[0]->shape_[1];
    std::vector<int> pred(batch_size, -1);
    std::vector<int> gt(batch_size, -1);
    for (int bs = 0; bs < batch_size; ++bs) {
        float max_prob = -1e9;
        int max_index = -1;
        int gt_index = -1;
        for (int nc = 0; nc < num_class; ++nc) {
            if (max_prob < bottom[0]->data_[bs * num_class + nc]) {
                max_prob = bottom[0]->data_[bs * num_class + nc];
                max_index = bs * num_class + nc;
            }
            if (bottom[1]->data_[bs * num_class + nc] == 1) {
                gt_index = bs * num_class + nc;
            }
        }
        pred[bs] = max_index;
        gt[bs] = gt_index;
    }
    int correct = 0;
    for (int i = 0; i < batch_size; ++i) {
        if (pred[i] == gt[i]) {
            ++correct;
        }
    }
    top[0]->data_[0] = float(correct) / batch_size;
}

void AccuracyLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {}

std::vector<std::shared_ptr<Bean>> AccuracyLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}
