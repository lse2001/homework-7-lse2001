#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H

#include <iostream>
#include <string>

class StringQueue {
private:
    // m_data = storage (dynamic array of strings, allows resizing)
    // m_dataSize = max size (capacity of the array)
    // m_count = current size (number of elements in queue)
    // m_front = where to remove (index of front element)
    // m_rear = where to add (index for next enqueue)

    // Note: m_data is a pointer instead of a fixed array (e.g., std::string m_data[8])
    // so we can dynamically resize the queue when it becomes full.

    std::string* m_data;
    size_t m_dataSize;
    size_t m_count;
    size_t m_front;
    size_t m_rear;

public:
    // default constructor initializes an empty queue with initial capacity
    StringQueue();

    // destructor frees dynamically allocated memory
    ~StringQueue();

    // copy constructor creates a deep copy of another queue
    StringQueue(const StringQueue& other);

    // copy assignment operator replaces current queue with deep copy of another
    StringQueue& operator=(const StringQueue& other);

    // move constructor transfers ownership of resources from a temporary queue
    StringQueue(StringQueue&& other);

    // move assignment operator transfers resources and avoids deep copy
    StringQueue& operator=(StringQueue&& other);

    // returns the number of elements currently in the queue
    size_t size() const;

    // returns how many elements can be added before resizing is needed
    size_t capacity() const;

    // resets the queue to an empty state without deallocating memory
    void clear();

    // adds a new element to the rear of the queue
    void enqueue(std::string value);

    // removes and returns the front element of the queue
    std::string dequeue();

    // outputs the queue contents in FIFO order
    friend std::ostream& operator<<(std::ostream& lhs, const StringQueue& rhs);
};

#endif