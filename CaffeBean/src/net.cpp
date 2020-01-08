//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/net.h"
#include "../include/layers/test_layer.h"


Net::Net() {
    std::cout << "constructing net..." << std::endl;
    std::unique_ptr<Layer> tl1(new TestLayer("tl1"));
    layers.push_back(std::move(tl1));
    std::unique_ptr<Layer> tl2(new TestLayer("tl2"));
    layers.push_back(std::move(tl2));
}

Net::~Net() {
    std::cout << "cleaning..." << std::endl;
}

void Net::print_net() {
    std::cout << "----------------------" << std::endl;
    std::cout << "layers include: " << std::endl;
    for (auto &layer : layers) {
        std::cout << layer->get_name() << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

Bean Net::forward() {
    for (auto &layer : layers) {
        layer->forward();
    }
    return Bean();
}

Bean Net::backward() {
    for (int i = layers.size() - 1; i >= 0; --i) {
        layers[i]->backward();
    }
    return Bean();
}

