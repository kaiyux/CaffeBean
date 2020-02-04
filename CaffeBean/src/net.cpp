//
// Created by Kaiyu Xie on 2019/12/22.
//

#include <layers/fully_connected_layer.h>
#include "../include/net.h"


Net::Net() {
    std::cout << "constructing net..." << std::endl;
    std::unique_ptr<Layer> fc1(new FullyConnectedLayer("fc1"));
    layers.push_back(std::move(fc1));
    std::unique_ptr<Layer> fc2(new FullyConnectedLayer("fc2"));
    layers.push_back(std::move(fc2));
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

Bean *Net::forward() {
    Bean *curBottom = new Bean(); //TODO: should be the top of input layer there
    for (auto &layer : layers) {
        layer->forward(curBottom);
        curBottom = layer->get_top();
    }
    return curBottom;
}

Bean *Net::backward() {
    Bean *curTop = new Bean(); //TODO: should be the bottom of loss layer there
    for (int i = layers.size() - 1; i >= 0; --i) {
        layers[i]->backward(curTop);
        curTop = layers[i]->get_bottom();
    }
    return curTop;
}

