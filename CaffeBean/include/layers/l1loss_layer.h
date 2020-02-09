//
// Created by Kaiyu Xie on 2020/2/8.
//

#ifndef CAFFEBEAN_L1LOSS_LAYER_H
#define CAFFEBEAN_L1LOSS_LAYER_H

#include "../layer.h"

class L1LossLayer : public Layer {
private:
    int reduction_;
public:
    L1LossLayer(const std::string &name);

    L1LossLayer(const std::string &name, int reduction);

    ~L1LossLayer();

    void init_layer();

    std::vector<Bean *> forward(std::vector<Bean *> &bottom);

    std::vector<Bean *> backward(std::vector<Bean *> &top);

    int get_reduction();

    static const int NONE = 0;
    static const int MEAN = 1;
    static const int SUM = 2;
};

#endif //CAFFEBEAN_L1LOSS_LAYER_H
