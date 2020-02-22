//
// Created by Kaiyu Xie on 2020/2/3.
//

#include "gtest/gtest.h"
#include <iostream>
#include "../CaffeBean/include/bean.h"
#include "../CaffeBean/include/layers/fully_connected_layer.h"
#include "../CaffeBean/include/layers/l1loss_layer.h"
#include "../CaffeBean/include/math_function.h"

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
    fc->init_layer();

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
}
// -------------------- FullyConnectedLayer --------------------

// -------------------- L1LossLayer --------------------
TEST(L1LossLayer, layer_init_test) {
    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    int none = L1LossLayer::NONE;
    ASSERT_EQ(l1->get_reduction(), none);

    L1LossLayer *l2 = new L1LossLayer("l2");
    int mean = L1LossLayer::MEAN;
    ASSERT_EQ(l2->get_reduction(), mean);

    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    int sum = L1LossLayer::SUM;
    ASSERT_EQ(l3->get_reduction(), sum);
}

TEST(L1LossLayer, layer_forward_test) {
    std::vector<int> input_shape = {3, 4};
    std::shared_ptr<Bean> input_bean = std::make_shared<Bean>(input_shape);
    std::shared_ptr<Bean> label = std::make_shared<Bean>(input_shape);
    std::vector<std::shared_ptr<Bean>> input = {input_bean, label};
    for (auto i:input) {
        normal(i.get());
    }

    std::vector<int> output_shape = {3, 4};
    std::shared_ptr<Bean> top_bean = std::make_shared<Bean>(output_shape);
    std::vector<std::shared_ptr<Bean>> output = {top_bean};

    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    l1->forward(input, output);
    display_matrix("none l1losslayer output", output[0]->data_, 3, 4);

    L1LossLayer *l2 = new L1LossLayer("l2");
    l2->forward(input, output);
    ASSERT_EQ(output[0]->size_, 1);
    display_matrix("mean l2losslayer output", output[0]->data_, 1, 1);

    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    l3->forward(input, output);
    ASSERT_EQ(output[0]->size_, 1);
    display_matrix("sum l3losslayer output", output[0]->data_, 1, 1);
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

    std::vector<int> output_shape = {3, 4};
    std::shared_ptr<Bean> top_bean = std::make_shared<Bean>(output_shape);
    std::vector<std::shared_ptr<Bean>> output = {top_bean};

    L1LossLayer *l1 = new L1LossLayer("l1", L1LossLayer::NONE);
    l1->forward(input, output);
    display_matrix("none l1losslayer loss", output[0]->data_, 3, 4);
    l1->backward(input, output);
    display_matrix("none l1losslayer diff", input[0]->diff_, 3, 4);
    display_matrix("none l1losslayer diff", input[1]->diff_, 3, 4);

    input = {input_bean, label};
    output = {top_bean};
    L1LossLayer *l2 = new L1LossLayer("l2");
    l2->forward(input, output);
    display_matrix("mean l2losslayer loss", output[0]->data_, 1, 1);
    l2->backward(input, output);
    display_matrix("mean l2losslayer diff", input[0]->diff_, 1, 1);
    display_matrix("mean l2losslayer diff", input[1]->diff_, 1, 1);

    input = {input_bean, label};
    output = {top_bean};
    L1LossLayer *l3 = new L1LossLayer("l3", L1LossLayer::SUM);
    l3->forward(input, output);
    display_matrix("sum l3losslayer loss", output[0]->data_, 1, 1);
    l3->backward(input, output);
    display_matrix("sum l3losslayer diff", input[0]->diff_, 1, 1);
    display_matrix("sum l3losslayer diff", input[1]->diff_, 1, 1);
}
// -------------------- L1LossLayer --------------------

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
}

TEST(Init, eye) {
    vector<int> shape = {4, 5};
    Bean *bean = new Bean(shape);
    eye(bean);
    display_matrix("eye", bean->data_, 4, 5);
}

TEST(Init, normal) {
    vector<int> shape = {4, 5};
    Bean *bean = new Bean(shape);
    normal(bean);
    display_matrix("normal", bean->data_, 4, 5);
    normal(bean, 10, 1);
    display_matrix("normal", bean->data_, 4, 5);
}
// -------------------- Init --------------------