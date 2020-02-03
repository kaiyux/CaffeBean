//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_TEST_LAYER_H
#define CAFFEBEAN_TEST_LAYER_H

#include "../layer.h"

class TestLayer : public Layer {
public:
    TestLayer(const std::string &name);

    Bean forward();

    Bean backward();
};

#endif //CAFFEBEAN_TEST_LAYER_H
