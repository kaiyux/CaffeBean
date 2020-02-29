//
// Created by Kaiyu Xie on 2020/2/24.
//

#ifndef CAFFEBEAN_LAYER_FACTORY_H
#define CAFFEBEAN_LAYER_FACTORY_H

#include "layer.h"
#include "config.h"
#include "common.h"
#include "layers/input_layer.h"
#include "layers/fully_connected_layer.h"
#include "layers/l1loss_layer.h"
#include "layers/relu_layer.h"

class LayerFactory {
public:
    std::unique_ptr<Layer> create_layer(const std::shared_ptr<Config> &config);
};

#endif //CAFFEBEAN_LAYER_FACTORY_H
