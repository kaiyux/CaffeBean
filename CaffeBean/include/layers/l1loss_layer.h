//
// Created by Kaiyu Xie on 2020/2/8.
//

#ifndef CAFFEBEAN_L1LOSS_LAYER_H
#define CAFFEBEAN_L1LOSS_LAYER_H

#include "../layer.h"

class L1LossLayer : public Layer {
private:
    int reduction_;
    Bean *diff_;
public:
    L1LossLayer(const std::string &name);

    L1LossLayer(const std::string &name, int reduction);

    ~L1LossLayer();

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();

    int get_reduction();

    static const int NONE = 0;
    static const int MEAN = 1;
    static const int SUM = 2;
};

#endif //CAFFEBEAN_L1LOSS_LAYER_H
