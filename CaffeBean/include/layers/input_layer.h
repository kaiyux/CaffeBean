//
// Created by Kaiyu Xie on 2020/2/4.
//

#ifndef CAFFEBEAN_INPUT_LAYER_H
#define CAFFEBEAN_INPUT_LAYER_H

#include "layer.h"
#include "dataset.h"

class InputLayer : public Layer {
private:
    std::vector<int> input_shape_, label_shape_;
    std::shared_ptr<Dataset> dataset_;
public:
    InputLayer(const std::string &name);

    InputLayer(const std::shared_ptr<Config> &config);

    ~InputLayer();

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();

    std::vector<Bean *> random_init(std::vector<int> &shape);
};

#endif //CAFFEBEAN_INPUT_LAYER_H
