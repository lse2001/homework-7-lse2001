#include "StringQueue.h"
#include <utility>

//-----RULE OF 6 FUNCTIONS------

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

// copy constructor
StringQueue::StringQueue(const StringQueue& other) {
    m_dataSize = other.m_dataSize;
    m_count = other.m_count;
    m_front = other.m_front;
    m_rear = other.m_rear;

    m_data = new std::string[m_dataSize];

    for (size_t i = 0; i < m_dataSize; i++) {
        m_data[i] = other.m_data[i];
    }
}

// copy assignment operator
StringQueue& StringQueue::operator=(const StringQueue& other) {
    if (this != &other) {
        delete[] m_data;

        m_dataSize = other.m_dataSize;
        m_count = other.m_count;
        m_front = other.m_front;
        m_rear = other.m_rear;

        m_data = new std::string[m_dataSize];

        for (size_t i = 0; i < m_dataSize; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    return *this;
}

// move constructor
StringQueue::StringQueue(StringQueue&& other) {
    m_data = other.m_data;
    m_dataSize = other.m_dataSize;
    m_count = other.m_count;
    m_front = other.m_front;
    m_rear = other.m_rear;

    other.m_data = nullptr;
    other.m_dataSize = 0;
    other.m_count = 0;
    other.m_front = 0;
    other.m_rear = 0;
}

// move assignment operator
StringQueue& StringQueue::operator=(StringQueue&& other) {
    if (this != &other) {
        std::swap(m_data, other.m_data);
        std::swap(m_dataSize, other.m_dataSize);
        std::swap(m_count, other.m_count);
        std::swap(m_front, other.m_front);
        std::swap(m_rear, other.m_rear);
    }

    return *this;
}

//-----FUNCTIONS-----

// returns number of elements
size_t StringQueue::size() const {
    return m_count;
}

// returns remaining capacity before resize
size_t StringQueue::capacity() const {
    return m_dataSize - m_count;
}

// clears the queue, future enqueues will overwrite  data that remains
void StringQueue::clear() {
    m_count = 0;
    m_front = 0;
    m_rear = 0;
}

void StringQueue::enqueue(std::string value) {
    // enqueue advances rear
    // dequeue advances front

    // resize if queue is full
    if (capacity() == 0) {

        // create new array with double capacity
        size_t newSize = m_dataSize * 2;
        std::string* newData = new std::string[newSize];

        // copy elements in FIFO order starting from front
        for (size_t i = 0; i < m_count; i++) {
            newData[i] = m_data[(m_front + i) % m_dataSize];
        }

        // free old array
        delete[] m_data;

        // point m_data to new array
        m_data = newData;

        // update array size
        m_dataSize = newSize;

        // reset front to beginning
        m_front = 0;

        // rear should point to next open position
        m_rear = m_count;
    }

    // place value at rear index
    m_data[m_rear] = value;

    // move rear forward with wrap-around
    m_rear = (m_rear + 1) % m_dataSize;

    // increase number of elements
    m_count++;
}

std::string StringQueue::dequeue() {
    // enqueue advances rear
    // dequeue advances front

    // store front element in temporary string
    std::string temp = m_data[m_front];

    // move front forward with wrap-around
    m_front = (m_front + 1) % m_dataSize;

    // decrease number of elements
    m_count--;

    // return removed value
    return temp;
}

std::ostream& operator<<(std::ostream& lhs, const StringQueue& rhs) {

    // loop through queue in FIFO order
    for (size_t i = 0; i < rhs.m_count; i++) {

        // compute actual array index with wrap-around
        size_t index = (rhs.m_front + i) % rhs.m_dataSize;

        // print current element
        lhs << rhs.m_data[index];

        // print comma between elements (not after last)
        if (i < rhs.m_count - 1) {
            lhs << ", ";
        }
    }

    return lhs;
}


//-----HELPERS FOR MAIN-----
size_t StringQueue::getFrontIndex() const {
    return m_front;
}

size_t StringQueue::getRearIndex() const {
    return m_rear;
}

size_t StringQueue::getDataSize() const {
    return m_dataSize;
}