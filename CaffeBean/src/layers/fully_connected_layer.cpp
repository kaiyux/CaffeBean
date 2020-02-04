//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../../include/layers/fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(const std::string &name) : Layer(name) {
    std::cout << "creating FullyConnectedLayer: " << name << " ..." << std::endl;
    k = 0.1;
    b = 0.1;
}

Bean *FullyConnectedLayer::forward(Bean *bottom) {
    std::cout << get_name() << " forward" << std::endl;
    return get_top();
}

Bean *FullyConnectedLayer::backward(Bean *top) {
    std::cout << get_name() << " backward" << std::endl;
    return get_bottom();
}

