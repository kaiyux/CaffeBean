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

    ~InputLayer();

    void init_layer();

    Bean *forward(std::vector<Bean *> bottom);

    Bean *backward(std::vector<Bean *> top);

    void random_init(std::vector<int> &shape);
};

#endif //CAFFEBEAN_INPUT_LAYER_H
