//
// Created by Kaiyu Xie on 2020/2/4.
//

#include "../../include/layers/input_layer.h"

InputLayer::InputLayer(const std::string &name) : Layer(name) {
    std::cout << "creating FullyConnectedLayer: " << name << " ..." << std::endl;
}

Bean *InputLayer::forward(Bean *bottom) {
    std::cout << get_name() << " forward" << std::endl;
    return get_top();
}

Bean *InputLayer::backward(Bean *top) {
    std::cout << get_name() << " backward" << std::endl;
    return get_bottom();
}
