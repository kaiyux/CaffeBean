//
// Created by Kaiyu Xie on 2020/4/11.
//

#ifndef CAFFEBEAN_SOFTMAX_LOSS_LAYER_H
#define CAFFEBEAN_SOFTMAX_LOSS_LAYER_H

#include "layer.h"

class SoftmaxWithLossLayer : public Layer {
private:
    float *prob_;
public:
    SoftmaxWithLossLayer(std::string name);

    SoftmaxWithLossLayer(const std::shared_ptr<Config> &config);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_SOFTMAX_LOSS_LAYER_H
