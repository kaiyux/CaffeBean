//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/bean.h"

Bean::Bean() {}

Bean::Bean(int num, int channel, int height, int width) {
    shape[0] = num;
    shape[1] = channel;
    shape[2] = height;
    shape[3] = width;
    size = num * channel * height * width;
    data = (float *) std::calloc(size, size * sizeof(float));
    diff = (float *) std::calloc(size, size * sizeof(float));
}

int Bean::N() {
    return this->shape[0];
}

int Bean::C() {
    return this->shape[1];
}

int Bean::H() {
    return this->shape[2];
}

int Bean::W() {
    return this->shape[3];
}

int Bean::getSize() {
    return this->size;
}
