//
// Created by Kaiyu Xie on 2020/3/24.
//

#ifndef CAFFEBEAN_IO_H
#define CAFFEBEAN_IO_H

#include "bean.h"

inline void save_model(const std::vector<std::shared_ptr<Bean>> &beans, const std::string &model_path) {
    const char *filename = model_path.data();
    FILE *pFile;
    if ((pFile = fopen(filename, "wb")) == nullptr) {
        CAFFEBEAN_LOG("file don't exists: " << filename);
        exit(0);
    }
    for (const auto &bean:beans) {
        fwrite(bean->data_, sizeof(float), bean->size_, pFile);
    }
    fclose(pFile);
}

inline void load_model(const std::vector<std::shared_ptr<Bean>> &beans, const std::string &model_path) {
    const char *filename = model_path.data();
    FILE *pFile;
    if ((pFile = fopen(filename, "rb")) == nullptr) {
        CAFFEBEAN_LOG("file don't exists: " << filename);
        exit(0);
    }
    for (const auto &bean:beans) {
        fread(bean->data_, sizeof(float), bean->size_, pFile);
    }
    fclose(pFile);
}

#endif //CAFFEBEAN_IO_H
