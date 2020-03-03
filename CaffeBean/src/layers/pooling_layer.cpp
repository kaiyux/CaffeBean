//
// Created by Kaiyu Xie on 2020/3/1.
//

#include "../../include/layers/pooling_layer.h"

PoolingLayer::PoolingLayer(std::string name, std::string type, int kernel_size, int stride, int padding, int dilation,
                           bool ceil_mode) : Layer(name) {
    CAFFEBEAN_ASSERT(type == "MAX" || type == "AVERAGE",
                     "type of PoolingLayer must be MAX or AVERAGE");

    type_ = type;
    kernel_size_ = kernel_size;
    stride_ = stride;
    padding_ = padding;
    dilation_ = dilation;
    ceil_mode_ = ceil_mode;
}

void PoolingLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing PoolingLayer: " << name_ << " ...");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() == 4, "bottom shape must be NCHW");

    N_ = bottom[0]->N();
    C_ = bottom[0]->C();
    H_in_ = bottom[0]->H();
    W_in_ = bottom[0]->W();

    const float H_out_tmp = (float(H_in_ + 2 * padding_ - dilation_ * (kernel_size_ - 1) - 1) / float(stride_)) + 1;
    const float W_out_tmp = (float(W_in_ + 2 * padding_ - dilation_ * (kernel_size_ - 1) - 1) / float(stride_)) + 1;
    if (ceil_mode_) {
        H_out_ = ceil(H_out_tmp);
        W_out_ = ceil(W_out_tmp);
    } else {
        H_out_ = floor(H_out_tmp);
        W_out_ = floor(W_out_tmp);
    }

    std::vector<int> top_shape = {N_, C_, H_out_, W_out_};
    top[0]->reshape(top_shape);
}

void PoolingLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    // TODO: take padding, dilation and stride into consideration
    if (type_ == "MAX") {
        int top_index = 0;
        for (int n = 0; n < N_; ++n) {
            for (int c = 0; c < C_; ++c) {
                for (int h = 0; h <= H_in_ - kernel_size_; ++h) {
                    for (int w = 0; w <= W_in_ - kernel_size_; ++w) {
                        float max_value = bottom[0]->data_[n * C_ * H_in_ * W_in_ + c * H_in_ * W_in_ + h * W_in_ + w];
                        int max_index = -1;
                        for (int kh = 0; kh < kernel_size_; ++kh) {
                            for (int kw = 0; kw < kernel_size_; ++kw) {
                                const int cur_index =
                                        n * C_ * H_in_ * W_in_ + c * H_in_ * W_in_ + (h + kh) * W_in_ + w + kw;
                                if (bottom[0]->data_[cur_index] > float(max_value)) {
                                    max_value = bottom[0]->data_[cur_index];
                                    max_index = cur_index;
                                }
                            }
                        }
                        top[0]->data_[top_index] = max_value;
                        max_index_.push_back(max_index);
                        ++top_index;
                    }
                }
            }
        }
    } else if (type_ == "AVERAGE") {
        //TODO: finish this :(
    } else {
        CAFFEBEAN_LOG("type " << type_ << " not implemented.");
    }
}

void PoolingLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    if (type_ == "MAX") {
        for (int i = 0; i < bottom[0]->size_; ++i) {
            bottom[0]->diff_[i] = 0;
        }
        for (int i = 0; i < top[0]->size_; ++i) {
            bottom[0]->diff_[max_index_[i]] = top[0]->diff_[i];
        }
    } else if (type_ == "AVERAGE") {

    } else {
        CAFFEBEAN_LOG("type " << type_ << " not implemented.");
    }
}

std::vector<std::shared_ptr<Bean>> PoolingLayer::get_learnable_beans() {
    return std::vector<std::shared_ptr<Bean>>();
}