//
// Created by Kaiyu Xie on 2020/4/7.
//

#include "dataset.h"

Dataset::Dataset(const std::string &label_file, int batch_size, int width, int height, bool shuffle) {
    label_file_ = label_file;
    batch_size_ = batch_size;
    width_ = width;
    height_ = height;
    cur_pos_ = 0;
    shuffle_ = shuffle;
    read_image_label(label_file_, images_, labels_);
    if (shuffle_) {
        // TODO: shuffle
    }
}

float *Dataset::next_batch() {
    auto *batch = new float[batch_size_ * 1 * height_ * width_]();
    for (int i = cur_pos_; i < cur_pos_ + batch_size_; ++i) {
        auto image = load_gray_img(images_[i]); // TODO: transform if image isn't of the shape wigth*height
        for (int j = 0; j < height_ * width_; ++j) {
            batch[(i - cur_pos_) * height_ * width_ + j] = image[j];
        }
    }
    cur_pos_ += batch_size_;
    if (cur_pos_ > images_.size() - 1) {
        cur_pos_ = 0;
    }

    return batch;
}

