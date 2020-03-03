//
// Created by Kaiyu Xie on 2020/2/24.
//

#include "../include/layer_factory.h"

std::unique_ptr<Layer> LayerFactory::create_layer(const std::shared_ptr<Config> &config) {
    const std::string type = config->get_type();
    if (type == "Input") {
        auto params = config->get_params();
        std::unique_ptr<Layer> input(new InputLayer(config->get_name()));
        CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
        return input;
    } else if (type == "FullyConnected") {
        auto params = config->get_params();
        std::unique_ptr<Layer> fc(new FullyConnectedLayer(config->get_name(),
                                                          params["in_features"],
                                                          params["out_features"],
                                                          params["has_bias"]));
        CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
        return fc;
    } else if (type == "L1Loss") {
        auto params = config->get_params();
        if (params.find("reduction") != params.end()) {
            std::unique_ptr<Layer> l1loss(new L1LossLayer(config->get_name(), params["reduction"]));
            CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
            return l1loss;
        } else {
            std::unique_ptr<Layer> l1loss(new L1LossLayer(config->get_name()));
            CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
            return l1loss;
        }
    } else if (type == "Relu") {
        std::unique_ptr<Layer> relu(new ReluLayer(config->get_name()));
        CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
        return relu;
    } else if (type == "Pooling") {
        auto params = config->get_params();
        std::string pool_type;
        if (params["type"] == 0) { //TODO: this shouldn't happen
            pool_type = "MAX";
        } else {
            pool_type = "AVERAGE";
        }
        std::unique_ptr<Layer> pooling(
                new PoolingLayer(config->get_name(), pool_type, params["kernel_size"], params["stride"],
                                 params["padding"], params["dilation"], params["ceil_mode"]));
        CAFFEBEAN_LOG(type << ": " << config->get_name() << " done.");
        return pooling;
    } else {
        CAFFEBEAN_LOG(type << ": " << config->get_name() << " not implmented.");
    }
}
