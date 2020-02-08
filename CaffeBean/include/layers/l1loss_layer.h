//
// Created by Kaiyu Xie on 2020/2/8.
//

#ifndef CAFFEBEAN_L1LOSS_LAYER_H
#define CAFFEBEAN_L1LOSS_LAYER_H

#include "../layer.h"

class L1LossLayer : public Layer {
private:
    std::string reduction_;
public:
    L1LossLayer(const std::string &name);

    L1LossLayer(const std::string &name, std::string reduction);

    ~L1LossLayer();

    void init_layer();

    Bean *forward(std::vector<Bean *> bottom);

    Bean *backward(std::vector<Bean *> top);

    std::string get_reduction();
};

#endif //CAFFEBEAN_L1LOSS_LAYER_H
