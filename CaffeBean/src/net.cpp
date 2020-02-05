//
// Created by Kaiyu Xie on 2019/12/22.
//

#include <layers/fully_connected_layer.h>
#include <layers/input_layer.h>
#include "../include/net.h"


Net::Net() {
    std::cout << "constructing net..." << std::endl;
    std::unique_ptr<Layer> fc1(new FullyConnectedLayer("fc1", 10, 20, true));
    layers_.push_back(std::move(fc1));
    std::unique_ptr<Layer> fc2(new FullyConnectedLayer("fc2", 20, 30, true));
    layers_.push_back(std::move(fc2));
}

Net::~Net() {}

void Net::print_net() {
    std::cout << "----------------------" << std::endl;
    std::cout << "layers include: " << std::endl;
    for (auto &layer : layers_) {
        std::cout << layer->get_name() << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

void Net::init_net() {
    for (auto &layer:layers_) {
        layer->init_layer();
    }
}

Bean *Net::forward() {
    std::unique_ptr<InputLayer> input_layer(new InputLayer("input_layer"));
    std::vector<int> input_shape = {5, 10};
    input_layer->random_init(input_shape);
    Bean *curBottom = input_layer->get_top();
    for (auto &layer : layers_) {
        layer->forward(curBottom);
        curBottom = layer->get_top();
    }
    return curBottom;
}

void Net::backward() {
    Bean *curTop = new Bean(); //TODO: should be the bottom of loss layer there
    for (int i = layers_.size() - 1; i >= 0; --i) {
        layers_[i]->backward(curTop);
        curTop = layers_[i]->get_bottom();
    }
}

