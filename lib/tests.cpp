//
// Created by Kaiyu Xie on 2020/2/3.
//

#include "gtest/gtest.h"
#include <iostream>
#include "../CaffeBean/include/bean.h"

using namespace std;

TEST(Bean, ExampleBean) {
    int testNum = 10, testChannel = 3, testHeight = 256, testWidth = 256;
    Bean *bean = new Bean(testNum, testChannel, testHeight, testWidth);
    EXPECT_EQ(bean->N(), testNum); //EXPECT_* fail, test continues
    ASSERT_EQ(bean->C(), testChannel); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->H(), testHeight); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->W(), testWidth); //ASSERT_* fail, test interrupts
    ASSERT_EQ(bean->getSize(), testNum * testChannel * testHeight * testWidth);
}

TEST(Layer, ExampleLayer) {
}