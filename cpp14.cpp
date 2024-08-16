#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct QueueElement {
        T value;
        int priority;
    };

    QueueElement* elements;
    int capacity;
    int size;

public:
    PriorityQueue(int initialCapacity = 10) {
        elements = new QueueElement[initialCapacity];
        capacity = initialCapacity;
        size = 0;
    }

    ~PriorityQueue() {
        delete[] elements;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    bool IsFull() const {
        return size == capacity;
    }

    void InsertWithPriority(const T& value, int priority) {
        if (IsFull()) {
            throw overflow_error("Queue is full");
        }

        int position = size;
        while (position > 0 && elements[position - 1].priority < priority) {
            elements[position] = elements[position - 1];
            position--;
        }

        elements[position].value = value;
        elements[position].priority = priority;
        size++;
    }

    T PullHighestPriorityElement() {
        if (IsEmpty()) {
            throw underflow_error("Queue is empty");
        }

        T result = elements[0].value;

        for (int i = 1; i < size; i++) {
            elements[i - 1] = elements[i];
        }

        size--;
        return result;
    }

    T Peek() const {
        if (IsEmpty()) {
            throw underflow_error("Queue is empty");
        }
        return elements[0].value;
    }

    int GetSize() const {
        return size;
    }

    void Show() const {
        for (int i = 0; i < size; i++) {
            cout << "Value: " << elements[i].value << ", Priority: " << elements[i].priority << endl;
        }
    }
};

int main() {
    PriorityQueue<string> queue;
    queue.InsertWithPriority("Apple", 3);
    queue.InsertWithPriority("Banana", 1);
    queue.InsertWithPriority("Cherry", 2);

    cout << "Peek: " << queue.Peek() << endl;
    cout << "Size: " << queue.GetSize() << endl;
    queue.Show();

    cout << "Pulled: " << queue.PullHighestPriorityElement() << endl;
    queue.Show();
}