#include <bits/stdc++.h>


template <class T>
class MaxQueue {
public:
    MaxQueue() : maxSize(INT32_MAX) {};
    MaxQueue(int size) : maxSize(size) {};

    void push(T element) {
        Q.push(element);
        if (Q.size() == 1) {
            minD.push_back(element); maxD.push_back(element);
            return;
        }
        while (!maxD.empty() && maxD.back() < element) { maxD.pop_back(); }
        while (!minD.empty() && minD.back() > element) { minD.pop_back(); }
        minD.push_back(element); maxD.push_back(element);
        if (Q.size() > maxSize) { pop(); }
    }

    void pop() {
        if (Q.front() == minD.front()) { minD.pop_front(); }
        if (Q.front() == maxD.front()) { maxD.pop_front(); }
        Q.pop();
    }

    T getMax() { return maxD.front(); }

    T getMin() { return minD.front(); }

    size_t size() const { return Q.size(); }

private:
    std::queue<T> Q; std::deque<T> minD, maxD;
    int maxSize{};
};

