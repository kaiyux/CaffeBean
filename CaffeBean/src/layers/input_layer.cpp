//
// Created by Kaiyu Xie on 2020/2/4.
//

#include "../../include/layers/input_layer.h"

InputLayer::InputLayer(const std::string &name) : Layer(name) {
    CAFFEBEAN_LOG("creating InputLayer: " << name << " ...");
}

InputLayer::InputLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {
    CAFFEBEAN_LOG("creating InputLayer: " << config->get_name() << " ...");
    auto params = config->get_params();
    for (const auto &i:params["input_shape"]) {
        input_shape_.push_back(i.asInt());
    }
    for (const auto &i:params["label_shape"]) {
        label_shape_.push_back(i.asInt());
    }
}

InputLayer::~InputLayer() {
    CAFFEBEAN_LOG("layer " << name_ << " deleted");
}

void InputLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing InputLayer: " << name_ << " ...");
    top[0]->reshape(input_shape_);
    top[1]->reshape(label_shape_);
}

void InputLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    // TODO: temporarily using given bean
    float input[6] = {6.87926, 4.36403, 5.73078, 5.96791, 5.55232, 5.73246};
    for (int i = 0; i < 2 * 3; ++i) {
        top[0]->data_[i] = input[i];
    }
    for (int i = 0; i < 2 * 5; ++i) {
        top[1]->data_[i] = float(i);
    }
}

void InputLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {}

std::vector<std::shared_ptr<Bean>> InputLayer::get_learnable_beans() {
    return {};
}

std::vector<Bean *> InputLayer::random_init(std::vector<int> &shape) {
    std::vector<Bean *> top;
    Bean *top_bean = new Bean(shape);
    normal(top_bean);
    top.push_back(top_bean);
    return top;
}
