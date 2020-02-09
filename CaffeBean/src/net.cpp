//
// Created by Kaiyu Xie on 2019/12/22.
//

#include <layers/fully_connected_layer.h>
#include <layers/input_layer.h>
#include "../include/net.h"


Net::Net() {
    CAFFEBEAN_LOG("constructing net...");
    std::unique_ptr<Layer> fc1(new FullyConnectedLayer("fc1", 10, 20, true));
    layers_.push_back(std::move(fc1));
    std::unique_ptr<Layer> fc2(new FullyConnectedLayer("fc2", 20, 30, true));
    layers_.push_back(std::move(fc2));
}

Net::~Net() {}

void Net::print_net() {
    CAFFEBEAN_LOG("----------------------");
    CAFFEBEAN_LOG("layers include: ");
    for (auto &layer : layers_) {
        CAFFEBEAN_LOG(layer->get_name());
    }
    CAFFEBEAN_LOG("----------------------");
}

void Net::init_net() {
    for (auto &layer:layers_) {
        layer->init_layer();
    }
}

std::vector<Bean *> Net::forward() {
    std::unique_ptr<InputLayer> input_layer(new InputLayer("input_layer"));
    std::vector<int> input_shape = {5, 10};
    std::vector<Bean *> cur_bottom = input_layer->random_init(input_shape);
    std::vector<Bean *> cur_top;
    for (auto &layer : layers_) {
        cur_top = layer->forward(cur_bottom);
        cur_bottom = cur_top;
    }
    return cur_bottom;
}

void Net::backward() {
    std::vector<Bean *> cur_bottom, cur_top;
    for (int i = layers_.size() - 1; i >= 0; --i) {
        cur_bottom = layers_[i]->backward(cur_top);
        cur_top = cur_bottom;
    }
}

