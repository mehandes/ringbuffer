#include <ringbuffer.h>
#include <stdexcept>

using namespace ringbuffer;

template<class T>
std::size_t RingBuffer<T>::next(std::size_t index) {
    return index == m_capacity - 1 ? 0 : ++index;
}

template<class T>
std::size_t RingBuffer<T>::prev(std::size_t index) {
    return index == 0 ? m_capacity - 1 : --index;
}

template<class T>
std::size_t RingBuffer<T>::next_virtual(std::size_t index) {
    return index == m_tail ? m_head : next(index);
}

template<class T>
RingBuffer<T>::RingBuffer(std::size_t capacity) 
    : m_capacity{capacity}, m_size{0}, m_head{0}, m_tail{0} {
        if (capacity == 0)
            throw std::invalid_argument("Capacity must be positive.");

        p_buffer = new T[capacity];
    }

template<class T>
RingBuffer<T>::~RingBuffer() {
    delete p_buffer;
}

template<class T>
void RingBuffer<T>::append(T value) {
    if (m_size++ == 0) {
        p_buffer[m_head] = value;
        return;
    }
        
    m_tail = next(m_tail);
    
    if (m_tail == m_head) m_head = next(m_head);
    if (m_size > m_capacity) m_size--;

    p_buffer[m_tail] = value;
}

template<class T>
T RingBuffer<T>::pop_head() {
    if (m_size == 0)
        throw std::out_of_range("Buffer is empty.");

    std::size_t ind = m_head;

    if (m_size > 1)
        m_head = next(m_head);
    
    m_size--;
    return p_buffer[ind];
}

template<class T>
T RingBuffer<T>::pop_tail() {
    if (m_size == 0)
        throw std::out_of_range("Buffer is empty.");

    std::size_t ind = m_tail;

    if (m_size > 1)
        m_tail = prev(m_tail);
    
    m_size--;
    return p_buffer[ind];
}

template<class T>
std::vector<T> RingBuffer<T>::operator()(std::size_t count, std::size_t offset) {
    if (count > m_size)
        throw std::out_of_range("Out of range.");

    std::vector<T> v(count);

    for (std::size_t i = 0, ind = (m_head + offset) % m_size; i < count; i++, ind = next_virtual(ind))
        v[i] = p_buffer[ind];
    
    return v;
}

template<class T>
std::size_t RingBuffer<T>::size() {
    return m_size;
}

template<class T>
std::size_t RingBuffer<T>::capacity() {
    return m_capacity;
}

template<class T>
T &RingBuffer<T>::operator[](std::size_t index) {
    if (index >= m_size)
        throw std::out_of_range("Out of range.");

    return p_buffer[(m_head + index) % m_capacity];
}

template<class T>
T &RingBuffer<T>::head() {
    if (m_size == 0)
        throw std::out_of_range("Buffer is empty.");

    return p_buffer[m_head];
}

template<class T>
T &RingBuffer<T>::tail() {
    if (m_size == 0)
        throw std::out_of_range("Buffer is empty.");

    return p_buffer[m_tail];
}

template class RingBuffer<int>;