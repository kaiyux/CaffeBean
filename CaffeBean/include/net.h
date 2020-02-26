//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_NET_H
#define CAFFEBEAN_NET_H

#include "common.h"
#include "layer.h"
#include "config.h"
#include "layer_factory.h"
#include "layers/fully_connected_layer.h"

class Net {
private:
    std::vector<std::unique_ptr<Layer>> layers_;

    std::vector<std::shared_ptr<Bean>> beans_;
    std::vector<std::shared_ptr<Bean>> learnable_beans_;

    std::vector<std::vector<std::shared_ptr<Bean>>> bottoms_;
    std::vector<std::vector<std::shared_ptr<Bean>>> tops_;

public:
    Net();

    ~Net();

    void init_net(std::vector<std::shared_ptr<Config>> configs);

    void forward();

    void backward();

    void print_net();
};

#endif //CAFFEBEAN_NET_H
