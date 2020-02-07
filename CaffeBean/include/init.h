//
// Created by Kaiyu Xie on 2020/2/4.
//

#ifndef CAFFEBEAN_INIT_H
#define CAFFEBEAN_INIT_H

#include "bean.h"
#include <random>

inline void constant(Bean *bean, float val) {
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = val;
        bean->diff_[i] = val;
    }
}

inline void ones(Bean *bean) {
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = 1;
        bean->diff_[i] = 1;
    }
}

inline void zeros(Bean *bean) {
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = 0;
        bean->diff_[i] = 0;
    }
}

inline void eye(Bean *bean) {
    CAFFEBEAN_ASSERT(bean->shape_.size() == 2, "The shape of input bean should be 2d.");
    int row = bean->shape_[0], col = bean->shape_[1];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == j) {
                bean->data_[i * bean->shape_[1] + j] = 1;
            } else {
                bean->data_[i * bean->shape_[1] + j] = 0;
            }
        }
    }
}

inline void normal(Bean *bean) {
    float mean = 0, std = 1;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<float> d{mean, std};
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = d(gen);
        bean->diff_[i] = d(gen);
    }
}

inline void normal(Bean *bean, float mean, float std) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<float> d{mean, std};
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = d(gen);
        bean->diff_[i] = d(gen);
    }
}

#endif //CAFFEBEAN_INIT_H
