//
// Created by nick on 15.04.2020.
//

#include "gtest/gtest.h"
#include "../Source/Connection/Connection.h"
TEST(get_socket_test, valid_data) {
    ASSERT_EQ(get_socket(), SUCCESS);
}

TEST(get_socket_test, not_valid_data) {
    ASSERT_EQ(get_socket(), FAIL);
}
