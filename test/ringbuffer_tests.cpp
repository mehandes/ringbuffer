#include <ringbuffer.h>
#include <gtest/gtest.h>
#include <exception>

using namespace ringbuffer;

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}