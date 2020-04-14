//
// Created by Kaiyu Xie on 2020/2/3.
//

#include "gtest/gtest.h"
#include <iostream>
#include "bean.h"

#include "layers/fully_connected_layer.h"
#include "layers/l1loss_layer.h"
#include "layers/relu_layer.h"
#include "layers/pooling_layer.h"
#include "layers/softmax_loss_layer.h"
#include "layers/conv_layer.h"

#include "math_function.h"
#include "solver.h"

using namespace std;

// -------------------- Bean --------------------
TEST(Bean, NCHW_init_bean) {
    int testNum = 10, testChannel = 3, testHeight = 256, testWidth = 256;
    Bean *bean = new Bean(testNum, testChannel, testHeight, testWidth);
    EXPECT_EQ(bean->N(), testNum); //EXPECT_* fail, test continues
    ASSERT_EQ(bean->C(), testChannel); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->H(), testHeight); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->W(), testWidth); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->size_, testNum * testChannel * testHeight * testWidth);
    delete bean;
}

TEST(Bean, vector_init_bean) {
    vector<int> shape = {1, 2, 3, 4, 5, 6};
    Bean *bean = new Bean(shape);
    ASSERT_EQ(bean->size_, 1 * 2 * 3 * 4 * 5 * 6);
    delete bean;
}
// -------------------- Bean --------------------

// -------------------- FullyConnectedLayer --------------------
TEST(FullyConnectedLayer, layer_init_test) {
    int in_features = 10, out_features = 20;
    bool has_bias = true;
    FullyConnectedLayer *fc = new FullyConnectedLayer("test_fc", in_features, out_features, has_bias);
    ASSERT_EQ(fc->get_name(), "test_fc");
    delete fc;
}

TEST(FullyConnectedLayer, layer_forward_backward_test) {
    std::vector<int> input_shape = {2, 3};
    std::shared_ptr<Bean> input_bean = std::make_shared<Bean>(input_shape);
    normal(input_bean.get());
    std::vector<int> output_shape = {2, 4};
    std::shared_ptr<Bean> output_bean = std::make_shared<Bean>(output_shape);
    vector<std::shared_ptr<Bean>> input, output;
    input.push_back(input_bean);
    output.push_back(output_bean);

    const int in_features = 3, out_features = 4;
    const bool has_bias = true;
    FullyConnectedLayer *fc = new FullyConnectedLayer("test_fc", in_features, out_features, has_bias);
    fc->init_layer(input, output);

    // forward
    fc->forward(input, output);

    ASSERT_EQ(output[0]->size_, 8);
    display_matrix("fc->bottom", input[0]->data_,
                   input[0]->size_ / input[0]->shape_.back(),
                   input[0]->shape_.back());
    display_matrix("fc->weight", fc->get_weight()->data_,
                   in_features, out_features);
    display_matrix("fc->bias", fc->get_bias()->data_,
                   1, out_features);
    display_matrix("fc->top", output[0]->data_,
                   output[0]->size_ / output[0]->shape_.back(),
                   output[0]->shape_.back());

    // backward
    std::vector<int> top_shape = {2, 4};
    std::shared_ptr<Bean> top_bean = std::make_shared<Bean>(top_shape);
    for (int i = 0; i < 8; ++i) {
        top_bean->diff_[i] = i - 4;
    }
    vector<std::shared_ptr<Bean>> top = {top_bean};

    fc->backward(input, top);

    ASSERT_EQ(input[0]->shape_, input[0]->shape_);
    display_matrix("fc->top diff", top[0]->diff_, 2, 4);
    display_matrix("fc->weight diff", fc->get_weight()->diff_,
                   in_features, out_features);
    display_matrix("fc->bias diff", fc->get_bias()->diff_,
                   1, out_features);
    display_matrix("fc->bottom diff", input[0]->diff_, 2, 3);

    delete fc;
}
// -------------------- FullyConnectedLayer --------------------

// -------------------- L1LossLayer --------------------
/*
TEST(L1LossLayer, layer_init_test) {
    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    int none = L1LossLayer::NONE;
    ASSERT_EQ(l1->get_reduction(), none);
    delete l1;

    L1LossLayer *l2 = new L1LossLayer("l2");
    int mean = L1LossLayer::MEAN;
    ASSERT_EQ(l2->get_reduction(), mean);
    delete l2;

    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    int sum = L1LossLayer::SUM;
    ASSERT_EQ(l3->get_reduction(), sum);
    delete l3;
}

TEST(L1LossLayer, layer_forward_test) {
    std::vector<int> input_shape = {3, 4};
    std::shared_ptr<Bean> input_bean = std::make_shared<Bean>(input_shape);
    std::shared_ptr<Bean> label = std::make_shared<Bean>(input_shape);
    std::vector<std::shared_ptr<Bean>> input = {input_bean, label};
    for (auto i:input) {
        normal(i.get());
    }

    std::vector<std::shared_ptr<Bean>> output1;
    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    l1->init_layer(input, output1);
    l1->forward(input, output1);
    display_matrix("none l1losslayer output", output1[0]->data_, 3, 4);
    delete l1;

    std::vector<std::shared_ptr<Bean>> output2;
    L1LossLayer *l2 = new L1LossLayer("l2");
    l2->init_layer(input, output2);
    l2->forward(input, output2);
    ASSERT_EQ(output2[0]->size_, 1);
    display_matrix("mean l1losslayer output", output2[0]->data_, 1, 1);
    CAFFEBEAN_LOG("111");
    output2.clear();
    delete l2;

    std::vector<std::shared_ptr<Bean>> output3;
    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    l3->init_layer(input, output3);
    l3->forward(input, output3);
    ASSERT_EQ(output3[0]->size_, 1);
    display_matrix("sum l1losslayer output", output3[0]->data_, 1, 1);
    output3.clear();
    delete l3;
}

TEST(L1LossLayer, layer_backward_test) {
    std::vector<int> input_shape = {3, 4};
    std::shared_ptr<Bean> input_bean = std::make_shared<Bean>(input_shape);
    std::shared_ptr<Bean> label = std::make_shared<Bean>(input_shape);
    std::vector<std::shared_ptr<Bean>> input = {input_bean, label};
    for (int i = 0; i < 12; ++i) {
        input[0]->data_[i] = i;
    }
    constant(input[1].get(), 5);

    std::vector<std::shared_ptr<Bean>> output1;
    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    l1->init_layer(input, output1);
    l1->forward(input, output1);
    display_matrix("none l1losslayer loss", output1[0]->data_, 3, 4);
    l1->backward(input, output1);
    display_matrix("none l1losslayer diff", input[0]->diff_, 3, 4);
    display_matrix("none l1losslayer diff", input[1]->diff_, 3, 4);
    delete l1;

    std::vector<std::shared_ptr<Bean>> output2;
    input = {input_bean, label};
    L1LossLayer *l2 = new L1LossLayer("l2");
    l2->init_layer(input, output2);
    l2->forward(input, output2);
    display_matrix("mean l2losslayer loss", output2[0]->data_, 1, 1);
    l2->backward(input, output2);
    display_matrix("mean l2losslayer diff", input[0]->diff_, 1, 1);
    display_matrix("mean l2losslayer diff", input[1]->diff_, 1, 1);
    delete l2;

    std::vector<std::shared_ptr<Bean>> output3;
    input = {input_bean, label};
    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    l3->init_layer(input, output3);
    l3->forward(input, output3);
    display_matrix("sum l3losslayer loss", output3[0]->data_, 1, 1);
    l3->backward(input, output3);
    display_matrix("sum l3losslayer diff", input[0]->diff_, 1, 1);
    display_matrix("sum l3losslayer diff", input[1]->diff_, 1, 1);
    delete l3;
}
 */
// -------------------- L1LossLayer --------------------

// -------------------- ReluLayer --------------------
TEST(ReluLayer, layer_test) {
    std::vector<std::shared_ptr<Bean>> bottom, top;
    std::vector<int> shape = {2, 5};
    auto bottom_bean = std::make_shared<Bean>(shape);
    for (int i = 0; i < bottom_bean->size_; ++i) {
        bottom_bean->data_[i] = float(i) - 5;
    }
    bottom.push_back(bottom_bean);
    std::shared_ptr<Bean> top_bean(new Bean());
    top.push_back(top_bean);

    auto relu = new ReluLayer("relu");
    relu->init_layer(bottom, top);
    relu->forward(bottom, top);

    for (int i = 0; i < top[0]->size_; ++i) {
        top[0]->diff_[i] = float(i);
    }

    relu->backward(bottom, top);

    display_matrix("bottom data", bottom_bean->data_, 2, 5);
    display_matrix("top data", top[0]->data_, 2, 5);
    display_matrix("top diff", top[0]->diff_, 2, 5);
    display_matrix("bottom diff", bottom_bean->diff_, 2, 5);

    delete relu;
}
// -------------------- ReluLayer --------------------

// -------------------- PoolingLayer --------------------
TEST(PoolingLayer, layer_test) {
    std::vector<std::shared_ptr<Bean>> bottom, top;
    std::vector<int> shape = {1, 1, 5, 5};
    auto bottom_bean = std::make_shared<Bean>(shape);
    for (int i = 0; i < bottom_bean->size_; ++i) {
        bottom_bean->data_[i] = float(i);
    }
    bottom.push_back(bottom_bean);
    std::shared_ptr<Bean> top_bean(new Bean());
    top.push_back(top_bean);

    auto maxpooling = new PoolingLayer("maxpooling", "MAX", 3, 1, 0, 1, true);
    maxpooling->init_layer(bottom, top);
    ASSERT_EQ(top[0]->size_, 9);

    maxpooling->forward(bottom, top);
    display_matrix("maxpooling input", bottom[0]->data_, 5, 5);
    display_matrix("maxpooling output", top[0]->data_, 3, 3);

    for (int i = 0; i < top[0]->size_; ++i) {
        top[0]->diff_[i] = float(i);
    }

    maxpooling->backward(bottom, top);
    display_matrix("maxpooling diff", bottom[0]->diff_, 5, 5);
}
// -------------------- PoolingLayer --------------------

// -------------------- SoftmaxWithLossLayer --------------------
TEST(SoftmaxWithLossLayer, layer_test) {
    auto softmax_loss = new SoftmaxWithLossLayer("softmax_loss");
    std::vector<std::shared_ptr<Bean>> bottom, top;
    std::vector<int> shape = {5};
    auto pred = std::make_shared<Bean>(shape);
    pred->data_[0] = 0.1;
    pred->data_[1] = 0.9;
    pred->data_[2] = 0.20;
    pred->data_[3] = 0.15;
    pred->data_[4] = 0.05;
    bottom.push_back(pred);
    auto label = std::make_shared<Bean>(shape);
    label->data_[0] = 0;
    label->data_[1] = 1;
    label->data_[2] = 0;
    label->data_[3] = 0;
    label->data_[4] = 0;
    bottom.push_back(label);

    softmax_loss->init_layer(bottom, top);

    softmax_loss->forward(bottom, top);
    CAFFEBEAN_LOG("loss = " << top[0]->data_[0]);

    softmax_loss->backward(bottom, top);
    display_matrix("diff", bottom[0]->diff_, bottom[0]->size_, 1);
}
// -------------------- SoftmaxWithLossLayer --------------------

// -------------------- ConvolutionLayer --------------------
TEST(ConvolutionLayer, layer_test) {
    auto conv = new ConvolutionLayer("conv", 3, 2, 2, 1, 0, 1, true);
    std::vector<std::shared_ptr<Bean>> bottom, top;
    std::vector<int> input_shape = {1, 3, 3, 3};
    auto input_features = std::make_shared<Bean>(input_shape);
    std::vector<int> nums = {1, 2, 0,
                             1, 1, 3,
                             0, 2, 2,
                             0, 2, 1,
                             0, 3, 2,
                             1, 1, 0,
                             1, 2, 1,
                             0, 1, 3,
                             3, 3, 2};
    for (int i = 0; i < nums.size(); ++i) {
        input_features->data_[i] = nums[i];
    }
    bottom.push_back(input_features);

    std::vector<int> output_shape = {1, 2, 2, 2};
    auto output_features = std::make_shared<Bean>(output_shape);
    top.push_back(output_features);

    conv->init_layer(bottom, top);

    conv->forward(bottom, top);

    for (int i = 0; i < top[0]->size_; ++i) {
        top[0]->diff_[i] = float(i);
    }
    conv->backward(bottom, top);
}
// -------------------- ConvolutionLayer --------------------

// -------------------- Math_fuction --------------------
TEST(Math_fuction, Eigen_test) {
    Eigen_test();
}

TEST(Math_fuction, matrix_add) {
    const int size = 12;
    auto *a = new float[size];
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }
    auto *b = new float[size];
    for (int i = 0; i < size; ++i) {
        b[i] = i;
    }
    auto *c = new float[size];
    matrix_add(a, b, c, 3, 4);
    display_matrix("a+b", c, 3, 4);
    delete[]a;
    delete[]b;
    delete[]c;
}

TEST(Math_fuction, matrix_sub) {
    const int size = 12;
    auto *a = new float[size];
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }
    auto *b = new float[size];
    for (int i = 0; i < size; ++i) {
        b[i] = i;
    }
    auto *c = new float[size];
    matrix_sub(a, b, c, 3, 4);
    display_matrix("a-b", c, 3, 4);
    delete[]a;
    delete[]b;
    delete[]c;
}

TEST(Math_fuction, matrix_multiply) {
    auto *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    auto *b = new float[30];
    for (int i = 0; i < 30; ++i) {
        b[i] = i;
    }
    auto *c = new float[24];
    matrix_multiply(a, b, c, 4, 5, 5, 6);
    delete[]a;
    delete[]b;
    delete[]c;
}

TEST(Math_fuction, matrix_abs) {
    auto *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = -i;
    }
    matrix_abs(a, a, 4, 5);
    display_matrix("abs", a, 4, 5);
    delete[]a;
}

TEST(Math_fuction, matrix_plus_constant) {
    auto *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    matrix_plus_constant(a, a, 10, 4, 5);
    display_matrix("abs", a, 4, 5);
    delete[]a;
}

TEST(Math_fuction, matrix_multiply_constant) {
    auto *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    matrix_multiply_constant(a, a, 10, 4, 5);
    display_matrix("abs", a, 4, 5);
    delete[]a;
}

TEST(Math_fuction, matrix_divide_constant) {
    auto *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    matrix_divide_constant(a, a, 5, 4, 5);
    display_matrix("abs", a, 4, 5);
    delete[]a;
}

TEST(Math_fuction, matrix_sum) {
    auto *a = new float[20];
    float sum = 0;
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
        sum += i;
    }
    ASSERT_EQ(matrix_sum(a, 4, 5), sum);
    delete[]a;
}

TEST(Math_fuction, matrix_transpose) {
    auto *a = new float[20];
    auto *b = new float[20]();
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    matrix_transpose(a, b, 5, 4);
    display_matrix("transpose", b, 4, 5);
    delete[]a;
    delete[]b;
}
// -------------------- Math_fuction --------------------

// -------------------- Init --------------------
TEST(Init, constant) {
    vector<int> shape = {1, 2, 3, 4, 5, 6};
    Bean *bean = new Bean(shape);
    float val = 6.6;
    constant(bean, val);
    for (int i = 0; i < bean->size_; ++i) {
        ASSERT_EQ(bean->data_[i], val);
        ASSERT_EQ(bean->diff_[i], val);
    }
    delete bean;
}

TEST(Init, ones) {
    vector<int> shape = {1, 2, 3, 4, 5, 6};
    Bean *bean = new Bean(shape);
    float val = 1;
    ones(bean);
    for (int i = 0; i < bean->size_; ++i) {
        ASSERT_EQ(bean->data_[i], val);
        ASSERT_EQ(bean->diff_[i], val);
    }
    delete bean;
}

TEST(Init, zeros) {
    vector<int> shape = {1, 2, 3, 4, 5, 6};
    Bean *bean = new Bean(shape);
    float val = 0;
    zeros(bean);
    for (int i = 0; i < bean->size_; ++i) {
        ASSERT_EQ(bean->data_[i], val);
        ASSERT_EQ(bean->diff_[i], val);
    }
    delete bean;
}

TEST(Init, eye) {
    vector<int> shape = {4, 5};
    Bean *bean = new Bean(shape);
    eye(bean);
    display_matrix("eye", bean->data_, 4, 5);
    delete bean;
}

TEST(Init, normal) {
    vector<int> shape = {4, 5};
    Bean *bean = new Bean(shape);
    normal(bean);
    display_matrix("normal", bean->data_, 4, 5);
    normal(bean, 10, 1);
    display_matrix("normal", bean->data_, 4, 5);
    delete bean;
}
// -------------------- Init --------------------

// -------------------- Solver --------------------
TEST(Solver, read_json) {
    std::string config_file = "/Users/kaiyu/workspace/CaffeBean/examples/test_net.json";
    float learning_rate = 0.01;
    int step = 10, display_step = 1;
    Solver *solver = new Solver(config_file, learning_rate, step, display_step);
    delete solver;
}
// -------------------- Solver --------------------