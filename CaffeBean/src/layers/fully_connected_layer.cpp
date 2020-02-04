//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../../include/layers/fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(const std::string &name, int in_features, int out_features, bool has_bias)
        : Layer(name) {
    std::cout << "creating FullyConnectedLayer: " << name << " ..." << std::endl;
    in_features_ = in_features;
    out_features_ = out_features;
    has_bias_ = has_bias;
    std::vector<int> weight_shape = {in_features_, out_features_};
    weight_ = new Bean(weight_shape);
}

void FullyConnectedLayer::init_layer() {

}

Bean *FullyConnectedLayer::forward(Bean *bottom) {
    std::cout << get_name() << " forward" << std::endl;
    return get_top();
}

Bean *FullyConnectedLayer::backward(Bean *top) {
    std::cout << get_name() << " backward" << std::endl;
    return get_bottom();
}


