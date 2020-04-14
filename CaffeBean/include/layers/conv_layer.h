//
// Created by Kaiyu Xie on 2020/4/12.
//

#ifndef CAFFEBEAN_CONV_LAYER_H
#define CAFFEBEAN_CONV_LAYER_H

#include "layer.h"

class ConvolutionLayer : public Layer {
private:
    int in_channels_;
    int out_channels_;
    int kernel_size_;
    int stride_;
    int padding_;
    int dilation_;
    bool has_bias_;

    std::shared_ptr<Bean> weight_, bias_;

    int N_, H_in_, W_in_, H_out_, W_out_;
public:
    ConvolutionLayer(std::string name, int in_channels, int out_channels, int kernel_size, int stride,
                     int padding, int dilation, bool has_bias);

    ConvolutionLayer(const std::shared_ptr<Config> &config);

    void init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    void backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top);

    std::vector<std::shared_ptr<Bean>> get_learnable_beans();
};

#endif //CAFFEBEAN_CONV_LAYER_H
