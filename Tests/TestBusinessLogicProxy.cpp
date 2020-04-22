//
// Created by nick on 15.04.2020.
//
#include "gtest/gtest.h"
#include "../Source/BusinessLogicProxy/BusinessLogicProxy.h"

#define SUCCESS 1
#define FAIL -1


TEST(enqueue_test, valid_data) {
    ASSERT_EQ(enquueu(), SUCCESS);
}

TEST(enqueue_test, not_valid_data) {
    ASSERT_EQ(enquueu(), FAIL);
}

TEST(dequeue_test, valid_data) {
    ASSERT_EQ(dequeue(), SUCCESS);
}

TEST(dequeue_test, not_valid_data) {
    ASSERT_EQ(dequeue(), FAIL);
}

TEST(watch_first_package_id_test, valid_data) {
    ASSERT_EQ(watch_first_package_id(), SUCCESS);
}

TEST(watch_first_package_id_test, not_valid_data) {
    ASSERT_EQ(watch_first_package_id(), FAIL);
}

