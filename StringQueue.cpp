#include "StringQueue.h"

// default constructor
StringQueue::StringQueue() {
    m_dataSize = 8;
    m_count = 0;
    m_front = 0;
    m_rear = 0;
    m_data = new std::string[m_dataSize];
}

// destructor
StringQueue::~StringQueue() {
    delete[] m_data;
}

// returns number of elements
size_t StringQueue::size() const {
    return m_count;
}

// returns remaining capacity before resize
size_t StringQueue::capacity() const {
    return m_dataSize - m_count;
}

// clears the queue
void StringQueue::clear() {
    m_count = 0;
    m_front = 0;
    m_rear = 0;
}