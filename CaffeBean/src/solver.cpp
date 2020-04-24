//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "solver.h"
#include "net.h"

Solver::Solver(std::string train_cfg) {
    read_train_config(train_cfg);
    read_net_config();
}

Solver::Solver(std::string config_file, float learning_rate, int step, int display_step) { // deprecated
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
        model_path_ = root["model_path"].asString();
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
            config->set_params(layer["params"]);
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

    CAFFEBEAN_LOG("start training...");
    auto tik = time(nullptr);
    for (int i = 0; i < step_; ++i) {
        if (i % display_step_ == 0) {
            CAFFEBEAN_LOG("--------------------");
            CAFFEBEAN_LOG("step: " << i);
            CAFFEBEAN_LOG("loss: " << net->get_loss());
            CAFFEBEAN_LOG("--------------------");
        }
        net->forward();
        net->backward();
        net->update(learning_rate_);
        net->zero_diff();
    }
    net->save(model_path_);
    auto tok = time(nullptr);
    CAFFEBEAN_LOG("total time: " << tok - tik << "s");
    CAFFEBEAN_LOG("loss: " << net->get_loss());
    CAFFEBEAN_LOG("training ended");
}

void Solver::infer() {
    Net *net = new Net();
    net->init_net(configs_);
    net->load(model_path_);

    CAFFEBEAN_LOG("inferring");
    auto tik = time(nullptr);
    float acc = 0;
    for (int i = 0; i < step_; ++i) {
        net->forward();
        acc += net->get_loss();
    }
    auto tok = time(nullptr);
    acc /= float(step_);

    CAFFEBEAN_LOG("total time: " << tok - tik << "s");
    CAFFEBEAN_LOG("acc: " << acc);
    CAFFEBEAN_LOG("inferring ended");
}


