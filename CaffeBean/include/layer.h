//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_LAYER_H
#define CAFFEBEAN_LAYER_H

#include "bean.h"
#include "common.h"
#include "init.h"
#include "math_function.h"

class Layer {
protected:
    std::vector<Bean *> top_;
    std::vector<Bean *> bottom_;
    std::string name_;
public:
    Layer(std::string name);

    virtual ~Layer();

    std::vector<Bean *> get_top();

    std::vector<Bean *> get_bottom();

    std::string get_name();

    virtual void init_layer() = 0;

    virtual std::vector<Bean *> forward(std::vector<Bean *> bottom) = 0;

    virtual std::vector<Bean *> backward(std::vector<Bean *> top) = 0;
};

#endif //CAFFEBEAN_LAYER_H
