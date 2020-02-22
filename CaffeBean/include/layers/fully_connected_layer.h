//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_FULLY_CONNECTED_LAYER_H
#define CAFFEBEAN_FULLY_CONNECTED_LAYER_H

#include "../layer.h"

class FullyConnectedLayer : public Layer {
private:
    int in_features_, out_features_;
    bool has_bias_;
    std::shared_ptr<Bean> weight_, bias_, bias_multiplier_;

public:
    FullyConnectedLayer(const std::string &name, int in_features, int out_features, bool has_bias);

    ~FullyConnectedLayer();

    void init_layer();

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    Bean *get_weight();

    Bean *get_bias();

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();

};

#endif //CAFFEBEAN_FULLY_CONNECTED_LAYER_H
