//
// Created by Kaiyu Xie on 2020/2/4.
//

#ifndef CAFFEBEAN_INPUT_LAYER_H
#define CAFFEBEAN_INPUT_LAYER_H

#include "layer.h"

class InputLayer : public Layer {
private:
public:
    InputLayer(const std::string &name);

    Bean *forward(Bean *bottom);

    Bean *backward(Bean *top);
};

#endif //CAFFEBEAN_INPUT_LAYER_H
