//
// Created by Kaiyu Xie on 2019/12/22.
//

#ifndef CAFFEBEAN_COMMON_H
#define CAFFEBEAN_COMMON_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <string>

#define CAFFEBEAN_ASSERT(expression, info)                                             \
    do {                                                                               \
        if(!(expression)){                                                             \
            std::cout<<"Assert failed: "<<__FILE__<<" line: "<<__LINE__<<std::endl;    \
            std::cout<<info<<std::endl;                                                \
            abort();                                                                   \
        }                                                                              \
    } while (0)

#endif //CAFFEBEAN_COMMON_H
