//
// Created by Kaiyu Xie on 2020/2/23.
//

#include "../include/solver.h"

void Solver::read_config(std::string config_file) {
    std::ifstream ifs;
    ifs.open(config_file);
    Json::Reader reader;
    Json::Value root;   // 'root' will contain the root value after parsing.
    if (reader.parse(ifs, root)) {
        std::cout << "Get config file: " << config_file << std::endl;
        std::string encoding = root.get("encoding", "UTF-8").asString();
        std::cout << encoding << std::endl;
        const Json::Value plugins = root["plug-ins"];
        for (int index = 0; index < plugins.size(); ++index)
            std::cout << plugins[index].asString() << " ";
        std::cout << std::endl;

        // Try other datatypes. Some are auto-convertible to others.
        std::cout << root["indent"].get("length", 3).asInt() << std::endl;
        std::cout << root["indent"].get("use_space", true).asBool() << std::endl;
        std::cout << root;
        std::cout << std::endl;
    }
    ifs.close();
}