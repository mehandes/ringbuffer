#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <cstdlib>
#include <vector>

namespace ringbuffer {
    template <class T>
    struct RingBuffer {
        private:
            T *p_buffer;
            std::size_t m_size;
            std::size_t m_capacity;
            std::size_t m_head;
            std::size_t m_tail;

            std::size_t next(std::size_t index);
            std::size_t prev(std::size_t index);
            std::size_t next_virtual(std::size_t index);

        public:
            RingBuffer(std::size_t capacity);
            ~RingBuffer();

            // Appends new element at the end. If buffer is full, overwrites oldest element.
            void append(T value);

            // Removes and returns oldest element. If buffer is empty, throws std::out_of_range.
            T pop_head();

            // Removes and returns last element. If buffer is empty, throws std::out_of_range.
            T pop_tail();

            // Returns std::vector with <count> elements of buffer staring from <offset>. Throws std::out_of_range.
            std::vector<T> operator()(std::size_t count, std::size_t offset);

            std::size_t size();
            std::size_t capacity();
            T &operator[](std::size_t index);
            T &head();
            T &tail();
    };
}

#endif // RINGBUFFER_H