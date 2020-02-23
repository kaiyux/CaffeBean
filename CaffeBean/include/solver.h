//
// Created by Kaiyu Xie on 2020/2/23.
//

#ifndef CAFFEBEAN_SOLVER_H
#define CAFFEBEAN_SOLVER_H

#include "../../lib/jsoncpp/include/json/json.h"
#include <iostream>
#include <fstream>

class Solver {
public:
    void read_config(std::string config_file);
};

#endif //CAFFEBEAN_SOLVER_H
