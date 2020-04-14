//
// Created by Kaiyu Xie on 2020/4/12.
//

#include "layers/conv_layer.h"

ConvolutionLayer::ConvolutionLayer(std::string name, int in_channels, int out_channels, int kernel_size, int stride,
                                   int padding, int dilation, bool has_bias) : Layer(name) {
    in_channels_ = in_channels;
    out_channels_ = out_channels;
    kernel_size_ = kernel_size;
    stride_ = stride;
    padding_ = padding;
    dilation_ = dilation;
    has_bias_ = has_bias;

    std::vector<int> kernel_shape = {out_channels_, in_channels_, kernel_size_, kernel_size_};
    weight_ = std::make_shared<Bean>(kernel_shape);
    if (has_bias_) {
        bias_ = std::make_shared<Bean>(kernel_shape);
    }
}

ConvolutionLayer::ConvolutionLayer(const std::shared_ptr<Config> &config) : Layer(config->get_name()) {
    auto params = config->get_params();
    in_channels_ = params["in_channels_"].asInt();
    out_channels_ = params["out_channels_"].asInt();
    kernel_size_ = params["kernel_size"].asInt();
    stride_ = params["stride"].asInt();
    padding_ = params["padding"].asInt();
    dilation_ = params["dilation"].asInt();
    has_bias_ = params["has_bias"].asBool();

    std::vector<int> weight_shape = {out_channels_, in_channels_, kernel_size_, kernel_size_};
    weight_ = std::make_shared<Bean>(weight_shape);
    if (has_bias_) {
        std::vector<int> bias_shape = {N_, out_channels_, H_out_, W_out_};
        bias_ = std::make_shared<Bean>(bias_shape);
    }
}

void ConvolutionLayer::init_layer(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    CAFFEBEAN_LOG("initializing ConvolutionLayer: " << name_ << " ...");
    CAFFEBEAN_ASSERT(bottom[0]->shape_.size() == 4, "bottom shape must be NCHW");
    N_ = bottom[0]->N();
    CAFFEBEAN_ASSERT(in_channels_ == bottom[0]->C(), "bottom channel != config");
    H_in_ = bottom[0]->H();
    W_in_ = bottom[0]->W();

    H_out_ = floor(float(H_in_ + 2 * padding_ - dilation_ * (kernel_size_ - 1) - 1) / float(stride_)) + 1;
    W_out_ = floor(float(W_in_ + 2 * padding_ - dilation_ * (kernel_size_ - 1) - 1) / float(stride_)) + 1;

    std::vector<int> top_shape = {N_, out_channels_, H_out_, W_out_};
    top[0]->reshape(top_shape);

    normal(weight_.get());
    if (has_bias_) {
        normal(bias_.get());
    }

    //test
    std::vector<int> nums = {1, 1,
                             2, 2,
                             1, 1,
                             1, 1,
                             0, 1,
                             1, 0,
                             1, 0,
                             0, 1,
                             2, 1,
                             2, 1,
                             1, 2,
                             2, 0};
    for (int i = 0; i < nums.size(); ++i) {
        weight_->data_[i] = nums[i];
    }
    //test
}

void ConvolutionLayer::forward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {
    // TODO: seems that something bad will happen if N != 1
    // TODO: take padding, dilation and stride into consideration
    // 1. im2col
    // feature map
    auto *input_matrix = new float[H_out_ * W_out_ * kernel_size_ * kernel_size_ * in_channels_]();
    int index = 0;
    for (int n = 0; n < N_; ++n) {
        for (int h = 0; h <= H_in_ - kernel_size_; ++h) {
            for (int w = 0; w <= W_in_ - kernel_size_; ++w) {
                for (int c = 0; c < in_channels_; ++c) {
                    for (int kh = 0; kh < kernel_size_; ++kh) {
                        for (int kw = 0; kw < kernel_size_; ++kw) {
                            const int cur_index =
                                    n * in_channels_ * H_in_ * W_in_ + c * H_in_ * W_in_ + (h + kh) * W_in_ + w + kw;
                            input_matrix[index] = bottom[0]->data_[cur_index];
                            ++index;
                        }
                    }
                }
            }
        }
    }

    // convolution kernel
    auto *conv_kernel_matrix = new float[out_channels_ * in_channels_ * kernel_size_ * kernel_size_]();
    index = 0;
    for (int oc = 0; oc < out_channels_; ++oc) {
        for (int ic = 0; ic < in_channels_; ++ic) {
            for (int kh = 0; kh < kernel_size_; ++kh) {
                for (int kw = 0; kw < kernel_size_; ++kw) {
                    const int cur_index =
                            oc * in_channels_ * kernel_size_ * kernel_size_ +
                            ic * kernel_size_ * kernel_size_ +
                            kh * kernel_size_ + kw;
                    conv_kernel_matrix[index] = weight_->data_[cur_index];
                    ++index;
                }
            }
        }
    }
    auto *conv_kernel_matrix_transpose = new float[out_channels_ * in_channels_ * kernel_size_ * kernel_size_]();
    matrix_transpose(conv_kernel_matrix, conv_kernel_matrix_transpose,
                     out_channels_, in_channels_ * kernel_size_ * kernel_size_);

    // 2. calculate
    auto *output_features = new float[H_out_ * W_out_ * out_channels_]();
    matrix_multiply(input_matrix, conv_kernel_matrix_transpose, output_features,
                    H_out_ * W_out_,
                    kernel_size_ * kernel_size_ * in_channels_,
                    in_channels_ * kernel_size_ * kernel_size_,
                    out_channels_);
    matrix_transpose(output_features, top[0]->data_, H_out_ * W_out_, out_channels_);

    //3. bias
    if (has_bias_) {
        auto *output_features_with_bias = new float[H_out_ * W_out_ * out_channels_]();
        matrix_add(output_features, bias_->data_, output_features_with_bias, H_out_ * W_out_, out_channels_);
        matrix_transpose(output_features_with_bias, top[0]->data_, H_out_ * W_out_, out_channels_);
    }

    delete[] input_matrix;
    delete[] conv_kernel_matrix;
    delete[] conv_kernel_matrix_transpose;
    delete[] output_features;
}

void ConvolutionLayer::backward(std::vector<std::shared_ptr<Bean>> &bottom, std::vector<std::shared_ptr<Bean>> &top) {

}

std::vector<std::shared_ptr<Bean>> ConvolutionLayer::get_learnable_beans() {
    if (has_bias_) {
        return {weight_, bias_};
    } else {
        return {weight_};
    }
}
