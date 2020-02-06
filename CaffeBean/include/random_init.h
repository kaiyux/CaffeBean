//
// Created by Kaiyu Xie on 2020/2/4.
//

#ifndef CAFFEBEAN_RANDOM_INIT_H
#define CAFFEBEAN_RANDOM_INIT_H

#include "bean.h"
#include <random>

inline void random_init_zero_one(Bean *bean) {
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0.0, 1.0);
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = u(e);
        bean->diff_[i] = u(e);
    }
}

inline void init_all_zero(Bean *bean) {
    for (int i = 0; i < bean->size_; ++i) {
        bean->data_[i] = 0;
        bean->diff_[i] = 0;
    }
}

#endif //CAFFEBEAN_RANDOM_INIT_H
