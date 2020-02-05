//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_BEAN_H
#define CAFFEBEAN_BEAN_H

#include "common.h"

class Bean {
public:
    int size_;
    std::vector<int> shape_;
    float *data_, *diff_;

    Bean();

    ~Bean();

    Bean(int num, int channel, int height, int width);

    Bean(std::vector<int> shape);

    int N();

    int C();

    int H();

    int W();
};

#endif //CAFFEBEAN_BEAN_H
