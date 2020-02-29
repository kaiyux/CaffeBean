//
// Created by Kaiyu Xie on 2020/2/29.
//

#ifndef CAFFEBEAN_RELU_LAYER_H
#define CAFFEBEAN_RELU_LAYER_H

#include "../layer.h"

class ReluLayer : public Layer {
public:
    ReluLayer(const std::string &name);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_RELU_LAYER_H
