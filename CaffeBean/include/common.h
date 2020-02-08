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

// Assert
#define CAFFEBEAN_ASSERT(expression, info)                                             \
    do {                                                                               \
        if(!(expression)){                                                             \
            std::cout<<"Assert failed: "<<__FILE__<<" line: "<<__LINE__<<std::endl;    \
            std::cout<<info<<std::endl;                                                \
            abort();                                                                   \
        }                                                                              \
    } while (0)

// Log
//TODO: can I accept several args at the same time?
#ifdef DEBUG
#define CAFFEBEAN_LOG(info) do{std::cout<<info<<std::endl;}while(0)
#else
#define CAFFEBEAN_LOG(info) (void)0
#endif

#endif //CAFFEBEAN_COMMON_H
