//
// Created by Kaiyu Xie on 2020/2/8.
//

#ifndef CAFFEBEAN_L1LOSS_LAYER_H
#define CAFFEBEAN_L1LOSS_LAYER_H

#include "../layer.h"

class L1LossLayer : public Layer {
private:
    std::string reduction_;
    Bean *diff_;
public:
    L1LossLayer(const std::shared_ptr<Config> &config);

    ~L1LossLayer();

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();

    std::string get_reduction();
};

#endif //CAFFEBEAN_L1LOSS_LAYER_H
