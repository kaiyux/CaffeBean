//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_NET_H
#define CAFFEBEAN_NET_H

#include "common.h"
#include "layer.h"

class Net {
private:
    std::vector<std::unique_ptr<Layer>> layers;
public:
    Net();

    ~Net();

    Bean *forward();

    Bean *backward();

    void print_net();
};

#endif //CAFFEBEAN_NET_H
