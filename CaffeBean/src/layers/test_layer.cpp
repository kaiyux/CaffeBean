//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../../include/layers/test_layer.h"

TestLayer::TestLayer(const std::string& name) : Layer(name) {
    std::cout << "creating TestLayer: " << name << " ..." << std::endl;
}

Bean TestLayer::forward() {
    std::cout << get_name() << " forward" << std::endl;
    return get_top();
}

Bean TestLayer::backward() {
    std::cout << get_name() << " backward" << std::endl;
    return get_bottom();
}


