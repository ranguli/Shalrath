#include <gtest/gtest.h>
#include "NetworkUtils.h"

TEST(NetworkUtilsTest, CheckInternetConnection) {
    bool isConnected = NetworkUtils::checkInternetConnection();
    EXPECT_TRUE(isConnected);
}
