//
// Created by Kaiyu Xie on 2020/2/24.
//

#ifndef CAFFEBEAN_LAYER_FACTORY_H
#define CAFFEBEAN_LAYER_FACTORY_H

#include "layer.h"
#include "config.h"
#include "common.h"
#include <map>

typedef std::unique_ptr<Layer> (*Creator)(const std::shared_ptr<Config> &);

class LayerFactory {
private:
    std::map<std::string, Creator> creator_registry_;
public:
    LayerFactory();

    void register_all_layers();

    void add_creator(const std::string &type, Creator creator_func);

    std::unique_ptr<Layer> create_layer(const std::shared_ptr<Config> &config);

#define STR(s) #s

#define ADD_CREATOR(type) \
    add_creator(STR(type), Create_##type##Layer);

#define REGISTER_LAYER(type) \
    std::unique_ptr<Layer> Create_##type##Layer(const std::shared_ptr<Config> &config){ \
        return std::unique_ptr<Layer>(new type##Layer(config)); \
    }
};

#endif //CAFFEBEAN_LAYER_FACTORY_H
