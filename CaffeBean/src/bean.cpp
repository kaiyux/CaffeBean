//
// Created by Kaiyu Xie on 2019/12/22.
//

#include "../include/bean.h"
#include <utility>

Bean::Bean() {}

Bean::Bean(int num, int channel, int height, int width) {
    shape_ = std::vector<int>(4);
    shape_[0] = num;
    shape_[1] = channel;
    shape_[2] = height;
    shape_[3] = width;
    size_ = num * channel * height * width;
    data_ = new float[size_]();
    diff_ = new float[size_]();
}

Bean::Bean(std::vector<int> shape) {
    shape_ = std::move(shape);
    size_ = 1;
    for (auto s:shape_) {
        size_ *= s;
    }
    data_ = new float[size_]();
    diff_ = new float[size_]();
}

Bean::~Bean() {
    delete[] data_;
    delete[] diff_;
}

int Bean::N() {
    return this->shape_[0];
}

int Bean::C() {
    return this->shape_[1];
}

int Bean::H() {
    return this->shape_[2];
}

int Bean::W() {
    return this->shape_[3];
}

void Bean::reshape(std::vector<int> shape) {
    shape_ = std::move(shape);
    size_ = 1;
    for (auto s:shape_) {
        size_ *= s;
    }
    data_ = new float[size_]();
    diff_ = new float[size_]();
}