//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_BEAN_H
#define CAFFEBEAN_BEAN_H

#include "common.h"

class Bean {
private:
    int size;
    std::vector<int> shape = std::vector<int>(4);
    float *data, *diff;
public:
    Bean();

    Bean(int num, int channel, int height, int width);

    int N();

    int C();

    int H();

    int W();

    int getSize();
};

#endif //CAFFEBEAN_BEAN_H
