//
// Created by Kaiyu Xie on 2020/2/3.
//

#include "gtest/gtest.h"
#include <iostream>
#include "../CaffeBean/include/bean.h"

using namespace std;

TEST(Bean, ExampleBean) {
    Bean *bean = new Bean(10, 3, 256, 256);
    EXPECT_EQ(bean->N(), 10); //EXPECT_* fail, test continues
    ASSERT_EQ(bean->C(), 3); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->H(), 256); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->W(), 256); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->getSize(), 10 * 3 * 256 * 256);
}

TEST(Layer, ExampleLayer) {
}