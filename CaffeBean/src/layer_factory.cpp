//
// Created by Kaiyu Xie on 2020/2/24.
//

#include "../include/layer_factory.h"

std::unique_ptr<Layer> LayerFactory::create_layer(const std::shared_ptr<Config> &config) {
    if (config->get_type() == "Input") {
        auto params = config->get_params();
        std::unique_ptr<Layer> input(new InputLayer(config->get_name()));
        CAFFEBEAN_LOG(config->get_type() << ": " << config->get_name() << " done.");
        return input;
    } else if (config->get_type() == "FullyConnected") {
        auto params = config->get_params();
        std::unique_ptr<Layer> fc(new FullyConnectedLayer(config->get_name(),
                                                          params["in_features"],
                                                          params["out_features"],
                                                          params["has_bias"]));
        CAFFEBEAN_LOG(config->get_type() << ": " << config->get_name() << " done.");
        return fc;
    } else if (config->get_type() == "L1Loss") {
        auto params = config->get_params();
        if (params.find("reduction") != params.end()) {
            std::unique_ptr<Layer> l1loss(new L1LossLayer(config->get_name(), params["reduction"]));
            CAFFEBEAN_LOG(config->get_type() << ": " << config->get_name() << " done.");
            return l1loss;
        } else {
            std::unique_ptr<Layer> l1loss(new L1LossLayer(config->get_name()));
            CAFFEBEAN_LOG(config->get_type() << ": " << config->get_name() << " done.");
            return l1loss;
        }
    } else {
        CAFFEBEAN_LOG(config->get_type() << ": " << config->get_name() << " not implmented.");
    }
}
