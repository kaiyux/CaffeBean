//
// Created by Kaiyu Xie on 2020/4/7.
//

#include "dataset.h"

Dataset::Dataset(const std::string &label_file, int num_class, int batch_size, int width, int height, bool shuffle) {
    label_file_ = label_file;
    num_class_ = num_class;
    batch_size_ = batch_size;
    width_ = width;
    height_ = height;
    cur_pos_ = 0;
    shuffle_ = shuffle;
    read_image_label(label_file_, images_, labels_);
    if (shuffle_) {
        // TODO: shuffle
    }
    mean_ = 0;
    std_ = 1;
}

std::vector<std::vector<float>> Dataset::next_batch() {
    std::vector<float> batch(batch_size_ * 1 * height_ * width_, 0);
    std::vector<float> label(batch_size_ * num_class_, 0);
    for (int i = cur_pos_; i < cur_pos_ + batch_size_; ++i) {
        auto image = load_gray_img(images_[i]); // TODO: transform if image isn't of the shape wigth*height
        for (int j = 0; j < height_ * width_; ++j) {
//            batch[(i - cur_pos_) * height_ * width_ + j] = (image[j] - mean_) / std_;
            batch[(i - cur_pos_) * height_ * width_ + j] = image[j] / 255;
        }
        label[(i - cur_pos_) * batch_size_ * num_class_ + labels_[i]] = 1;
    }
    cur_pos_ += batch_size_;
    if (cur_pos_ > images_.size() - 1) {
        cur_pos_ = 0;
    }
    return {batch, label};
}

void Dataset::set_mean(float mean) {
    mean_ = mean;
}

void Dataset::set_std(float std) {
    std_ = std;
}

