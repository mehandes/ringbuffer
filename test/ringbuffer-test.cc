#include "src/ringbuffer.h"
#include <gtest/gtest.h>
#include <exception>

using namespace ringbuffer;

TEST(RingBufferTest, ConstructValid) {
    RingBuffer<int> buffer{10};

    ASSERT_EQ(buffer.capacity(), 10);
    ASSERT_EQ(buffer.size(), 0);
}

TEST(RingBufferTest, ContructZeroCapacity) {
    RingBuffer<int> *buffer;
    ASSERT_THROW(buffer = new RingBuffer<int>(0), std::invalid_argument);
}

TEST(RingBufferTest, AppendEmpty) {
    RingBuffer<int> buffer{10};
    buffer.append(20);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer.head(), 20);
    ASSERT_EQ(buffer.tail(), 20);
}

TEST(RingBufferTest, AppendFull) {
    RingBuffer<int> buffer{2};
    buffer.append(1);
    buffer.append(2);
    
    buffer.append(3);

    ASSERT_EQ(buffer.size(), 2);
    ASSERT_EQ(buffer.head(), 2);
    ASSERT_EQ(buffer.tail(), 3);
}

TEST(RingBufferTest, PopHeadEmpty) {
    RingBuffer<int> buffer{2};
    ASSERT_THROW(buffer.pop_head(), std::out_of_range);
}

TEST(RingBufferTest, PopHeadNotEmpty) {
    RingBuffer<int> buffer{2};
    buffer.append(1);
    
    int i = buffer.pop_head();

    ASSERT_EQ(i, 1);
    ASSERT_EQ(buffer.size(), 0);
}

TEST(RingBufferTest, PopTailEmpty) {
    RingBuffer<int> buffer{2};
    ASSERT_THROW(buffer.pop_tail(), std::out_of_range);
}

TEST(RingBufferTest, PopTailNotEmpty) {
    RingBuffer<int> buffer{2};
    buffer.append(1);

    int i = buffer.pop_tail();

    ASSERT_EQ(i, 1);
    ASSERT_EQ(buffer.size(), 0);
}

TEST(RingBufferTest, GetRangeValid) {
    RingBuffer<int> buffer{3};
    buffer.append(1);
    buffer.append(2);
    buffer.append(3);

    std::vector<int> v = buffer(3, 0);

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
}

TEST(RingBufferTest, GetRangeCountOutOfRange) {
    RingBuffer<int> buffer{3};
    buffer.append(1);
    buffer.append(2);
    buffer.append(3);

    ASSERT_THROW(buffer(4, 0), std::out_of_range);
}

TEST(RingBufferTest, GetRangeOffsetOutOfRange) {
    RingBuffer<int> buffer{3};
    buffer.append(1);
    buffer.append(2);
    buffer.append(3);

    std::vector<int> v = buffer(2, 1);

    ASSERT_EQ(v[0], 2);
    ASSERT_EQ(v[1], 3);
}

TEST(RingBufferTest, GetElementEmpty) {
    RingBuffer<int> buffer{2};

    ASSERT_THROW(buffer[0], std::out_of_range);
}

TEST(RingBufferTest, GetElementOutOfRange) {
    RingBuffer<int> buffer{2};
    buffer.append(1);

    ASSERT_THROW(buffer[1], std::out_of_range);
}

TEST(RingBufferTest, GetHeadEmpty) {
    RingBuffer<int> buffer{2};

    ASSERT_THROW(buffer.head(), std::out_of_range);
}

TEST(RingBufferTest, GetTailEmpty) {
    RingBuffer<int> buffer{2};

    ASSERT_THROW(buffer.tail(), std::out_of_range);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}