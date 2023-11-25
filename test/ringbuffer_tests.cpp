#include <ringbuffer.h>
#include <gtest/gtest.h>
#include <exception>

using namespace ringbuffer;

TEST(RingBufferTests, ConstructValid) {
    RingBuffer<int> buffer{10};

    ASSERT_EQ(buffer.capacity(), 10);
    ASSERT_EQ(buffer.size(), 0);
}

TEST(RingBufferTests, ContructZeroCapacity) {
    RingBuffer<int> *buffer;
    ASSERT_THROW(buffer = new RingBuffer<int>(0), std::invalid_argument);
    ASSERT_EQ(buffer, nullptr);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}