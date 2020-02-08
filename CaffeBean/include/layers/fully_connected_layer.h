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
    Bean *weight_, *bias_;
public:
    FullyConnectedLayer(const std::string &name, int in_features, int out_features, bool has_bias);

    ~FullyConnectedLayer();

    void init_layer();

    std::vector<Bean *> forward(std::vector<Bean *> bottom);

    std::vector<Bean *> backward(std::vector<Bean *> top);

    Bean *get_weight();

    Bean *get_bias();

};

#endif //CAFFEBEAN_FULLY_CONNECTED_LAYER_H
