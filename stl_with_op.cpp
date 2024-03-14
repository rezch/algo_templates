#include <bits/stdc++.h>


template <class T>
class MinQueue { // queue with O(1) min/max, O(1) deque, O(n) enqueue
public:
    std::queue<T> Q; std::deque<T> D;
    void enque_element(T element) {
        Q.push(element);
        if (Q.size() == 1) { D.push_back(element); return; }
        while (!D.empty() && D.back() > element) { D.pop_back(); }
        D.push_back(element);
    }

    void deque_element() {
        if (Q.front() == D.front()) { D.pop_front(); }
        Q.pop();
    }

    T getMin() { return D.front(); }

    T getMax() { return D.back(); }
};

