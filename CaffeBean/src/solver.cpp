//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "../include/solver.h"

Solver::Solver(std::string config_file) {
    config_file_ = config_file;
    read_config();
}

void Solver::read_config() {
    std::ifstream ifs;
    ifs.open(config_file_);
    Json::Reader reader;
    Json::Value root;   // 'root' will contain the root value after parsing.
    if (reader.parse(ifs, root)) {
        std::cout << "Get config file: " << config_file_ << std::endl;
        std::cout << root;
        std::cout << std::endl;
        for (auto layer:root) {
            std::shared_ptr<Config> config(new Config());
            config->set_name(layer["name"].asString());
            config->set_type(layer["type"].asString());
            for (auto bottom:layer["bottoms"]) {
                config->add_bottom(bottom.asString());
            }
            for (auto top:layer["bottoms"]) {
                config->add_bottom(top.asString());
            }
            configs_.push_back(std::move(config));
        }
    } else {
        std::cout << "Something's wrong with file: " << config_file_ << std::endl;
    }
    ifs.close();
}

std::vector<std::shared_ptr<Config>> Solver::get_configs() {
    return configs_;
}

void Solver::solve() {

}
