//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_LAYER_H
#define CAFFEBEAN_LAYER_H


#include "bean.h"
#include "common.h"

class Layer {
private:
    Bean top;
    Bean bottom;
    std::string name;
public:
    Layer(std::string name);

    ~Layer();

    Bean get_top();

    Bean get_bottom();

    std::string get_name();

    void set_name(std::string name);

    virtual Bean forward();

    virtual Bean backward();
};

#endif //CAFFEBEAN_LAYER_H
