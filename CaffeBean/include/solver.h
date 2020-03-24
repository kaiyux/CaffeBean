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
    std::string model_path_;
    std::vector<std::shared_ptr<Config>> configs_;
    float learning_rate_;
    int step_, display_step_;
public:
    Solver(std::string train_cfg);

    Solver(std::string config_file, float learning_rate_, int step, int display_step);

    void read_train_config(std::string);

    void read_net_config();

    // TODO: check the availability of config file

    std::vector<std::shared_ptr<Config>> get_configs();

    void solve();

    void infer();
};

#endif //CAFFEBEAN_SOLVER_H
