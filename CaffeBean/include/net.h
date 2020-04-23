//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_NET_H
#define CAFFEBEAN_NET_H

#include "common.h"
#include "layer.h"
#include "config.h"
#include "layer_factory.h"
#include "io.h"

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

    void update(float learning_rate);

    void zero_diff();

    void save(std::string path);

    void load(std::string path);

    float *get_output();

    float get_loss();
};

#endif //CAFFEBEAN_NET_H
