//
// Created by Kaiyu Xie on 2020/4/23.
//

#ifndef CAFFEBEAN_ACCURACY_LAYER_H
#define CAFFEBEAN_ACCURACY_LAYER_H

#include "layer.h"

class AccuracyLayer : public Layer {
public:
    AccuracyLayer(const std::shared_ptr<Config> &config);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_ACCURACY_LAYER_H
