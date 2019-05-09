#include <gtest/gtest.h>
#include <google_test_boilerplate.hpp>

TEST(Check, get) {
    ASSERT_TRUE(!get());
}