//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_FULLY_CONNECTED_LAYER_H
#define CAFFEBEAN_FULLY_CONNECTED_LAYER_H

#include "../layer.h"

class FullyConnectedLayer : public Layer {
private:
    double k, b;
public:
    FullyConnectedLayer(const std::string &name);

    Bean *forward(Bean *bottom);

    Bean *backward(Bean *top);
};

#endif //CAFFEBEAN_FULLY_CONNECTED_LAYER_H
