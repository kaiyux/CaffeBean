//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "../include/solver.h"
#include "../include/net.h"

Solver::Solver(std::string config_file) {
    config_file_ = config_file;
    read_config();
    // TODO: check the availability of config file
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
            for (const auto &bottom:layer["bottoms"]) {
                config->add_bottom(bottom.asString());
            }
            for (const auto &top:layer["bottoms"]) {
                config->add_top(top.asString());
            }
            auto param_keys = layer["params"].getMemberNames();
            for (auto &param_key : param_keys) {
                config->add_params(param_key, layer["params"][param_key].asInt());
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
    Net *net = new Net();
    net->init_net(configs_);
    net->forward();
    CAFFEBEAN_LOG("net forward done");
    net->backward();
    CAFFEBEAN_LOG("net backward done");
}
