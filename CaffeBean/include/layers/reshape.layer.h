//
// Created by Kaiyu Xie on 2020/4/14.
//

#ifndef CAFFEBEAN_RESHAPE_LAYER_H
#define CAFFEBEAN_RESHAPE_LAYER_H

#include "layer.h"

class ReshapeLayer : public Layer {
private:
    std::vector<int> input_shape_, output_shape_;
public:
    ReshapeLayer(const std::shared_ptr<Config> &config);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_RESHAPE_LAYER_H
