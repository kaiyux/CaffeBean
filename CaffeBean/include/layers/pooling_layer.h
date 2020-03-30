//
// Created by Kaiyu Xie on 2020/3/1.
//

#ifndef CAFFEBEAN_POOLING_LAYER_H
#define CAFFEBEAN_POOLING_LAYER_H

#include "../layer.h"

class PoolingLayer : public Layer {
private:
    std::string type_;
    int kernel_size_;
    int stride_;
    int padding_;
    int dilation_;
    bool ceil_mode_;
    // TODO: kernel_size, stride, padding, dilation should be vector in the future

    int N_, C_, H_in_, W_in_, H_out_, W_out_;

    std::vector<int> max_index_;

    static const int MAX = 0;
    static const int AVERAGE = 1;

public:
    PoolingLayer(std::string name, std::string type, int kernel_size, int stride, int padding, int dilation,
                 bool ceil_mode);

    PoolingLayer(const std::shared_ptr<Config> &config);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_POOLING_LAYER_H
