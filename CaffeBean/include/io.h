//
// Created by Kaiyu Xie on 2020/3/24.
//

#ifndef CAFFEBEAN_IO_H
#define CAFFEBEAN_IO_H

#include "bean.h"
#include <fstream>
#include <regex>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>

namespace bg = boost::gil;

inline void read_image_label(const std::string &label_file,
                             std::vector<std::string> &images, std::vector<int> &labels) {
    CAFFEBEAN_LOG("Reading label file...");
    std::ifstream infile;
    infile.open(label_file.data());
    CAFFEBEAN_ASSERT(infile.is_open(), "can't open label file.");

    std::string s;
    while (getline(infile, s)) {
        std::regex ws_re("\t");
        std::vector<std::string> v(std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1),
                                   std::sregex_token_iterator());
        images.push_back(v[0]);
        labels.push_back(std::stoi(v[1]));
    }
    infile.close();
}

struct gray_pixel_inserter {
    std::vector<float> *storage;

    gray_pixel_inserter(std::vector<float> *s) : storage(s) {}

    void operator()(boost::gil::gray8_pixel_t p) const {
        storage->push_back(boost::gil::at_c<0>(p));
    }
};

// TODO:rgb image support
inline std::vector<float> load_gray_img(const std::string &path) {
    bg::gray8_image_t image;
    bg::read_image(path, image, bg::jpeg_tag{});
    const int width = image.width();
    const int height = image.height();
    std::vector<float> img;
    img.reserve(width * height * bg::num_channels<bg::gray8_image_t>());
    for_each_pixel(const_view(image), gray_pixel_inserter(&img));
    return img;
}

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
