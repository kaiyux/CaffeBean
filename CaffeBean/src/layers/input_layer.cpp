//
// Created by Kaiyu Xie on 2020/2/4.
//

#include "layers/input_layer.h"

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
    dataset_ = std::make_shared<Dataset>(
            params["label_file"].asString(), params["num_class"].asInt(), params["batch_size"].asInt(),
            params["width"].asInt(), params["height"].asInt(), params["shuffle"].asBool());
    if (params["mean"]) {
        dataset_->set_mean(params["mean"].asFloat());
    }
    if (params["std"]) {
        dataset_->set_std(params["std"].asFloat());
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
    auto next_batch = dataset_->next_batch();
    auto input = next_batch[0];
    auto label = next_batch[1];
    for (int i = 0; i < input.size(); ++i) {
        top[0]->data_[i] = input[i];
    }
    for (int i = 0; i < label.size(); ++i) {
        top[1]->data_[i] = label[i];
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
