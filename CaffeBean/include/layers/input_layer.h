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

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();

    std::vector<Bean *> random_init(std::vector<int> &shape);
};

#endif //CAFFEBEAN_INPUT_LAYER_H
