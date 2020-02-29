//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/net.h"
#include <layers/fully_connected_layer.h>
#include <layers/l1loss_layer.h>
#include <layers/input_layer.h>

Net::Net() {}

Net::~Net() {}

void Net::init_net(std::vector<std::shared_ptr<Config>> configs) {
    CAFFEBEAN_LOG("constructing net...");

    // 1. create layer
    int num_beans = 0;
    std::unordered_map<std::string, int> layer_name_to_index;
    LayerFactory *layer_factory = new LayerFactory();
    for (int i = 0; i < configs.size(); ++i) {
        auto layer = layer_factory->create_layer(configs[i]);

        num_beans += configs[i]->get_tops().size();

        auto learnable_beans = layer->get_learnable_beans();
        for (const auto &bean:learnable_beans) {
            learnable_beans_.push_back(bean);
        }

        layer_name_to_index[configs[i]->get_name()] = i;

        layers_.push_back(std::move(layer));
        bottoms_.emplace_back();
        tops_.emplace_back();
    }
    delete layer_factory;

    // 2. create & assign beans
    for (int i = 0; i < num_beans; ++i) {
        std::shared_ptr<Bean> bean(new Bean());
        beans_.push_back(bean);
    }

    int cur_bean = 0;
    for (int i = 0; i < configs.size(); ++i) {
        auto cur_bottoms = configs[i]->get_bottoms();
        for (const auto &cur_bottom:cur_bottoms) {
            bottoms_[i].push_back(beans_[cur_bean]);
            tops_[layer_name_to_index[cur_bottom]].push_back(beans_[cur_bean]);

            CAFFEBEAN_LOG("bean: " << cur_bean);
            CAFFEBEAN_LOG("bottom of : " << layers_[i]->get_name());
            CAFFEBEAN_LOG("top of : " << layers_[layer_name_to_index[cur_bottom]]->get_name());

            ++cur_bean;
        }
    }

    // 3. init layer (including setup the shape of beans)
    for (int i = 0; i < layers_.size(); ++i) {
        layers_[i]->init_layer(bottoms_[i], tops_[i]);
    }
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

void Net::update(float learning_rate) {
    for (auto bean:learnable_beans_) {
        auto *delta = new float[bean->size_]();
        matrix_multiply_constant(bean->diff_, delta, -learning_rate, 1, bean->size_);
        matrix_add(bean->data_, delta, bean->data_, 1, bean->size_);
    }
}

float *Net::get_output() {
    return tops_[tops_.size() - 2][0]->data_;
}

float Net::get_loss() {
    auto loss_bean = tops_.back()[0];
    return matrix_sum(loss_bean->data_, 1, loss_bean->size_);
}
