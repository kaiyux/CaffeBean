//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_NET_H
#define CAFFEBEAN_NET_H

#include "common.h"
#include "layer.h"

class Net {
private:
    std::vector<std::unique_ptr<Layer>> layers_;
public:
    Net();

    ~Net();

    void init_net();

    Bean *forward();

    void backward();

    void print_net();
};

#endif //CAFFEBEAN_NET_H
