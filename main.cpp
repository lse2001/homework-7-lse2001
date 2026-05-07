#include <iostream>
#include "StringQueue.h"
#include <utility>

void testRearWrapAround() {
    std::cout << "Test 1: Rear wrap-around\n\n";

    StringQueue q;

    // fill queue to capacity
    q.enqueue("A");
    q.enqueue("B");
    q.enqueue("C");
    q.enqueue("D");
    q.enqueue("E");
    q.enqueue("F");
    q.enqueue("G");
    q.enqueue("H");

    std::cout << "Queue after filling:\n";
    std::cout << q << "\n";

    std::cout << "Front index: " << q.getFrontIndex() << "\n";
    std::cout << "Rear index: " << q.getRearIndex() << "\n";
    std::cout << "Size: " << q.size() << "\n";
    std::cout << "Array size: " << q.getDataSize() << "\n\n";

    // dequeue one item so there is space at front
    std::cout << "Dequeued: " << q.dequeue() << "\n\n";

    std::cout << "Queue after dequeue:\n";
    std::cout << q << "\n";

    std::cout << "Front index: " << q.getFrontIndex() << "\n";
    std::cout << "Rear index: " << q.getRearIndex() << "\n\n";

    // enqueue another item
    q.enqueue("I");

    std::cout << "Queue after enqueueing I:\n";
    std::cout << q << "\n";

    std::cout << "Front index: " << q.getFrontIndex() << "\n";
    std::cout << "Rear index: " << q.getRearIndex() << "\n";
    std::cout << "Size: " << q.size() << "\n";
    std::cout << "Array size: " << q.getDataSize() << "\n\n";
}

void testResizeAndFrontReset() {
    std::cout << "Test 2: Resize and front reset\n\n";

    StringQueue q;

    // fill queue
    q.enqueue("A");
    q.enqueue("B");
    q.enqueue("C");
    q.enqueue("D");
    q.enqueue("E");
    q.enqueue("F");
    q.enqueue("G");
    q.enqueue("H");

    std::cout << "Queue before dequeue x3.\n";
    std::cout << q << "\n";

    // dequeue a few items so front is no longer 0
    q.dequeue();
    q.dequeue();
    q.dequeue();

    std::cout << "Queue after dequeue and before resize:\n";
    std::cout << q << "\n";

    std::cout << "Front index before resize: "
              << q.getFrontIndex() << "\n";

    std::cout << "Rear index before resize: "
              << q.getRearIndex() << "\n";

    std::cout << "Array size before resize: "
              << q.getDataSize() << "\n\n";

    // enqueue enough items to trigger resize
    q.enqueue("I");
    q.enqueue("J");
    q.enqueue("K");
    q.enqueue("L");

    std::cout << "Queue after adding elements to resize:\n";
    std::cout << q << "\n";

    std::cout << "Front index after resize: "
              << q.getFrontIndex() << "\n";

    std::cout << "Rear index after resize: "
              << q.getRearIndex() << "\n";

    std::cout << "Array size after resize: "
              << q.getDataSize() << "\n";

    std::cout << "Size: "
              << q.size() << "\n\n";
}

void testEmptyQueueReuse() {
    std::cout << "Test 3: Empty queue reuse with front not at 0\n\n";

    StringQueue q;

    // enqueue elements
    q.enqueue("A");
    q.enqueue("B");
    q.enqueue("C");
    q.enqueue("D");

    std::cout << "Initial queue:\n";
    std::cout << q << "\n";

    std::cout << "Front index: "
              << q.getFrontIndex() << "\n";

    std::cout << "Rear index: "
              << q.getRearIndex() << "\n\n";

    // dequeue everything
    std::cout << "Dequeuing all elements:\n";

    while (q.size() > 0) {
        std::cout << "Dequeued: "
                  << q.dequeue() << "\n";
    }

    std::cout << "\nQueue is now empty\n";

    // front should NOT be 0 here
    std::cout << "Front index after emptying queue: "
              << q.getFrontIndex() << "\n";

    std::cout << "Rear index after emptying queue: "
              << q.getRearIndex() << "\n\n";

    // prove queue still works after becoming empty
    q.enqueue("New A");
    q.enqueue("New B");

    std::cout << "Queue after enqueueing again:\n";
    std::cout << q << "\n";

    std::cout << "Front index: "
              << q.getFrontIndex() << "\n";

    std::cout << "Rear index: "
              << q.getRearIndex() << "\n";

    std::cout << "Size: "
              << q.size() << "\n\n";
}

void testCopyConstructorDeepCopy() {
    std::cout << "Test 4: Copy constructor deep copy\n\n";

    StringQueue original;

    original.enqueue("A");
    original.enqueue("B");
    original.enqueue("C");

    std::cout << "Original before copy:\n";
    std::cout << original << "\n\n";

    {
        // copy constructor is called here
        StringQueue copy(original);

        copy.enqueue("D");
        copy.dequeue();

        std::cout << "Modified copy inside scope:\n";
        std::cout << copy << "\n\n";
    }

    std::cout << "Original after modified copy goes out of scope:\n";
    std::cout << original << "\n\n";
}

void testMoveAssignmentFromTemporary() {
    std::cout << "Test 5: Move assignment from temporary queue\n\n";

    StringQueue movedQueue;

    if (true) {
        StringQueue temp;

        temp.enqueue("Move A");
        temp.enqueue("Move B");
        temp.enqueue("Move C");

        std::cout << "Temporary queue before move:\n";
        std::cout << temp << "\n\n";

        // move assignment is called here
        movedQueue = std::move(temp);

        std::cout << "Moved queue inside if statement:\n";
        std::cout << movedQueue << "\n\n";
    }

    // temp is destroyed here, but movedQueue should still be valid
    std::cout << "Moved queue after temp goes out of scope:\n";
    std::cout << movedQueue << "\n\n";

    movedQueue.enqueue("Move D");

    std::cout << "Moved queue after enqueueing another value:\n";
    std::cout << movedQueue << "\n\n";
}

int main() {
    char choice = ' ';

    while (choice != 'Q' && choice != 'q') {
        std::cout << "\nTest the following:\n"
                  << "1. Cause the rear index to wrap around to 0, by filling up the queue, then enqueuing again after at least one element has been dequeued.\n"
                  << "2. Cause the queue to resize, and make sure that the front element is back at index 0, even though it wasn't before.\n"
                  << "3. Enqueue and dequeue until the queue is empty, but front is not at index 0. Make sure you can still enqueue and have everything work after that.\n"
                  << "4. Copy-construct a queue, let it go out of scope, and make sure that it didn't delete an array owned by the queue it copied.\n"
                  << "5. Construct a temporary queue in an if statement, enqueue some values, and then move-assign it to an existing queue. Let the temporary go out of scope and be destroyed. Make sure it didn't delete its original array that is now being used by the queue it was move-assigned to.\n"
                  << "Q. Quit.\n\n";

        std::cout << "Enter test number: ";
        std::cin >> choice;
        std::cout << "\n";

        if (choice == '1') {
            testRearWrapAround();
        }
        else if (choice == '2') {
            testResizeAndFrontReset();
        }
        else if (choice == '3') {
            testEmptyQueueReuse();
        }
        else if (choice == '4') {
            testCopyConstructorDeepCopy();
        }
        else if (choice == '5') {
            testMoveAssignmentFromTemporary();
        }
        else if (choice == 'Q' || choice == 'q') {
            std::cout << "Exiting program.\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}