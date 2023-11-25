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

        public:
            RingBuffer(std::size_t capacity);
            ~RingBuffer();

            // Appends new element at the end
            void append(T value);

            // Removes and returns newest element from buffer 
            T pop_head();

            // Removes and returns oldest element from buffer
            T pop_tail();

            // Returns std::vector with <count> elements of buffer staring from <offset>
            std::vector<T> operator()(std::size_t count, std::size_t offset);

            std::size_t size();
            std::size_t capacity();
            T& head();
            T& tail();
    };
}

#endif // RINGBUFFER_H