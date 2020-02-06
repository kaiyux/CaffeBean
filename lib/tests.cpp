//
// Created by Kaiyu Xie on 2020/2/3.
//

#include "gtest/gtest.h"
#include <iostream>
#include "../CaffeBean/include/bean.h"
#include "../CaffeBean/include/layers/fully_connected_layer.h"
#include "../CaffeBean/include/math_function.h"

using namespace std;

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

    cout << "random init" << endl;
    random_init_zero_one(bean);
    for (int i = 0; i < bean->size_; ++i) {
        cout << bean->data_[i] << " ";
    }
    cout << endl;

    cout << "init all to zero" << endl;
    init_all_zero(bean);
    for (int i = 0; i < bean->size_; ++i) {
        cout << bean->data_[i] << " ";
    }
    cout << endl;

    delete bean;
}

TEST(FullyConnectedLayer, layer_init_test) {
    int in_features = 10, out_features = 20;
    bool has_bias = true;
    FullyConnectedLayer *fc = new FullyConnectedLayer("test_fc", in_features, out_features, has_bias);
    ASSERT_EQ(fc->get_name(), "test_fc");
    delete fc;
}

TEST(FullyConnectedLayer, layer_forward_test) {
    Bean *input = new Bean({2, 3});
    int in_features = 3, out_features = 5;
    bool has_bias = true;
    FullyConnectedLayer *fc = new FullyConnectedLayer("test_fc", in_features, out_features, has_bias);

    fc->init_layer();
    fc->forward(input);

    ASSERT_EQ(fc->get_top()->size_, 10);
    display_matrix("fc->bottom", fc->get_bottom()->data_,
                   fc->get_bottom()->size_ / fc->get_bottom()->shape_.back(),
                   fc->get_bottom()->shape_.back());
    display_matrix("fc->weight", fc->get_weight()->data_,
                   fc->get_weight()->shape_[0], fc->get_weight()->shape_[1]);
    display_matrix("fc->top", fc->get_top()->data_,
                   fc->get_top()->size_ / fc->get_top()->shape_.back(),
                   fc->get_top()->shape_.back());
}

TEST(Math_fuction, Eigen_test) {
    Eigen_test();
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