//
// Created by Kaiyu Xie on 2020/2/23.
//

#ifndef CAFFEBEAN_SOLVER_H
#define CAFFEBEAN_SOLVER_H

#include "../../lib/jsoncpp/include/json/json.h"
#include <iostream>
#include <fstream>
#include "config.h"

class Solver {
private:
    std::string config_file_;
    std::vector<std::shared_ptr<Config>> configs_;
public:
    Solver(std::string config_file);

    void read_config();

    std::vector<std::shared_ptr<Config>> get_configs();

    void solve();
};

#endif //CAFFEBEAN_SOLVER_H
