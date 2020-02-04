//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_LAYER_H
#define CAFFEBEAN_LAYER_H


#include "bean.h"
#include "common.h"

class Layer {
private:
    Bean *top_;
    Bean *bottom_;
    std::string name_;
public:
    Layer(std::string name);

    ~Layer();

    Bean *get_top();

    Bean *get_bottom();

    std::string get_name();

    virtual void init_layer() = 0;

    virtual Bean *forward(Bean *bottom) = 0;

    virtual Bean *backward(Bean *top) = 0;
};

#endif //CAFFEBEAN_LAYER_H
