//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "../include/solver.h"
#include "../include/net.h"

Solver::Solver(std::string train_cfg) {
    read_train_config(train_cfg);
    read_net_config();
}

Solver::Solver(std::string config_file, float learning_rate, int step, int display_step) {
    config_file_ = config_file;
    learning_rate_ = learning_rate;
    step_ = step;
    display_step_ = display_step;
    read_net_config();
}

void Solver::read_train_config(std::string train_cfg) {
    std::ifstream ifs;
    ifs.open(train_cfg);
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(ifs, root)) {
        std::cout << "Get config file: " << train_cfg << std::endl;
        std::cout << root;
        std::cout << std::endl;
        config_file_ = root["net"].asString();
        learning_rate_ = root["lr"].asFloat();
        step_ = root["step"].asInt();
        display_step_ = root["display_step"].asInt();;
    } else {
        std::cout << "Something's wrong with file: " << config_file_ << std::endl;
    }
    ifs.close();
}

void Solver::read_net_config() {
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

    for (int i = 0; i < step_; ++i) {
        if (i % display_step_ == 0) {
            CAFFEBEAN_LOG("step: " << i);
            CAFFEBEAN_LOG("loss: " << net->get_loss());
            display_matrix("output", net->get_output(), 2, 5);
        }
        net->forward();
        net->backward();
        net->update(learning_rate_);
    }
    CAFFEBEAN_LOG("loss: " << net->get_loss());
    display_matrix("output", net->get_output(), 2, 5);
}
