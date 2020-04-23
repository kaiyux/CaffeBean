//
// Created by Kaiyu Xie on 2020/4/7.
//

#ifndef CAFFEBEAN_DATASET_H
#define CAFFEBEAN_DATASET_H

#include <string>
#include "io.h"

class Dataset {
private:
    std::string label_file_;
    int num_class_;
    int batch_size_;
    int width_;
    int height_;
    int cur_pos_;
    bool shuffle_;
    float mean_;
    float std_;
    std::vector<std::string> images_;
    std::vector<int> labels_;
public:
    Dataset(const std::string &label_file, int num_class, int batch_size, int width, int height, bool shuffle);

    std::vector<std::vector<float>> next_batch();

    void set_mean(float mean);

    void set_std(float std);
};

#endif //CAFFEBEAN_DATASET_H
