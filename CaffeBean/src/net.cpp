//
// Created by Kaiyu Xie on 2019/12/22.
//

#include <layers/fully_connected_layer.h>
#include <layers/l1loss_layer.h>
#include <layers/input_layer.h>
#include "../include/net.h"


Net::Net() {}

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
    CAFFEBEAN_LOG("constructing net...");
    // TODO: This process should be done in a loop
    std::unique_ptr<Layer> fc1(new FullyConnectedLayer("fc1", 3, 4, true));
    fc1->init_layer();
    std::shared_ptr<Bean> fc1_bottom_bean(new Bean({2, 3}));
    beans_.push_back(fc1_bottom_bean);
    bottoms_.push_back({fc1_bottom_bean});
    std::shared_ptr<Bean> fc1_top_bean(new Bean({2, 4}));
    beans_.push_back(fc1_top_bean);
    tops_.push_back({fc1_top_bean});
    auto fc1_learnable_beans = fc1->get_learnable_beans();
    for (const auto &bean:fc1_learnable_beans) {
        learnable_beans_.push_back(bean);
    }
    layers_.push_back(std::move(fc1));

    std::unique_ptr<Layer> fc2(new FullyConnectedLayer("fc2", 4, 5, true));
    fc2->init_layer();
    bottoms_.push_back(tops_[0]);
    std::shared_ptr<Bean> fc2_top_bean(new Bean({2, 5}));
    beans_.push_back(fc2_top_bean);
    tops_.push_back({fc2_top_bean});
    auto fc2_learnable_beans = fc2->get_learnable_beans();
    for (const auto &bean:fc2_learnable_beans) {
        learnable_beans_.push_back(bean);
    }
    layers_.push_back(std::move(fc2));

    std::unique_ptr<Layer> l1loss(new L1LossLayer("l1loss", L1LossLayer::NONE));
    l1loss->init_layer();
    std::shared_ptr<Bean> label(new Bean({2, 5}));
    std::vector<std::shared_ptr<Bean>> l1loss_bottom;
    l1loss_bottom.push_back(beans_.back());
    l1loss_bottom.push_back(label);
    bottoms_.push_back(l1loss_bottom);
    std::shared_ptr<Bean> l1loss_top_bean(new Bean({2, 5}));
    beans_.push_back(l1loss_top_bean);
    tops_.push_back({l1loss_top_bean});
    auto l1loss_learnable_beans = l1loss->get_learnable_beans();
    for (const auto &bean:fc2_learnable_beans) {
        learnable_beans_.push_back(bean);
    }
    layers_.push_back(std::move(l1loss));
}

void Net::forward() {
    for (int i = 0; i < layers_.size(); ++i) {
        layers_[i]->forward(bottoms_[i], tops_[i]);
    }
}

void Net::backward() {
    for (int i = layers_.size() - 1; i >= 0; --i) {
        layers_[i]->backward(bottoms_[i], tops_[i]);
    }
}
