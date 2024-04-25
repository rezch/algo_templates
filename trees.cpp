#include <bits/stdc++.h>


namespace SegmentTree {
    template <class T>
    struct BitSegTree { // segment tree with binary inner calculation
        explicit BitSegTree(const std::vector<T> &a) : size_(a.size()), tree_(size_ << 1) {
            for (int i = 0; i < size_; ++i) { tree_[i + size_].value_ = a[i]; }
            for (int i = size_ - 1; i > 0; --i) { tree_[i] = merge(tree_[i << 1], tree_[i << 1 | 1]); }
        }

        void set_base_value(T value) { base_value = value; }

        void update(size_t i, T value) {
            tree_[i += size_].value_ = value;
            for (; i > 1; i >>= 1) { tree_[i >> 1] = merge(tree_[i], tree_[i ^ 1]); }
        }

        T get(size_t l, size_t r) const {
            T result = base_value;
            for (l += size_, r += size_; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) { result = combine(result, tree_[l++].value_); }
                if (!(r & 1)) { result = combine(result, tree_[r--].value_); }
            }
            return result;
        }

    private:
        struct Node { T value_; };

        static T combine(T lhs, T rhs) { return lhs + rhs; }

        static Node merge(Node node1, Node node2) {
            return Node{ .value_ = combine(node1.value_, node2.value_) };
        }

        size_t size_{};
        std::vector<Node> tree_;
        T base_value{};
    };

    struct SegTree { // Segment tree with addition on segment and assignment on segment
        explicit SegTree(int size) : size_(size), tree_(size_ << 2, 0), add_(size_ << 2, 0), push_(size_ << 2, -1) {}

        void Add(int l, int r, int value) {
            Add(1, 0, size_ - 1, l, r, (int64_t)value);
        }

        void Set(int l, int r, int value) {
            Set(1, 0, size_ - 1, l, r, (int64_t)value);
        }

        int64_t Get(int l, int r) {
            return Get(1, 0, size_ - 1, l, r);
        }

    private:
        void Push(int v, int l, int r) {
            if (push_[v] != -1) { // push push
                if (l != r) {
                    push_[v << 1] = push_[v << 1 | 1] = push_[v];
                    add_[v << 1] = add_[v << 1 | 1] = 0;
                }
                tree_[v] = 1LL * push_[v] * (r - l + 1);
                push_[v] = -1;
            }

            if (l != r) { // push add
                add_[v << 1] += add_[v];
                add_[v << 1 | 1] += add_[v];
            }
            tree_[v] += 1LL * add_[v] * (r - l + 1);
            add_[v] = 0;
        }

        int64_t Get(int v, int tl, int tr, int l, int r) {
            Push(v, tl, tr);
            if (l > r) { return 0; }
            if (l == tl && r == tr) { return tree_[v]; }

            int mid = (tl + tr) >> 1;
            return Get(v << 1, tl, mid, l, std::min(mid, r)) + Get(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r);
        }

        void Set(int v, int tl, int tr, int l, int r, int64_t value) {
            Push(v, tl, tr);
            if (l > r) { return; }
            if (l == tl && r == tr) {
                push_[v] = value;
                add_[v] = 0;
                Push(v, l, r);
                return;
            }
            int mid = (tl + tr) >> 1;
            Set(v << 1, tl, mid, l, std::min(mid, r), value);
            Set(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r, value);
            tree_[v] = tree_[v << 1] + tree_[v << 1 | 1];
        }

        void Add(int v, int tl, int tr, int l, int r, int64_t value) {
            Push(v, tl, tr);
            if (l > r) { return; }
            if (l == tl && r == tr) {
                add_[v] += value;
                Push(v, l, r);
                return;
            }
            int mid = (tl + tr) >> 1;
            Add(v << 1, tl, mid, l, std::min(mid, r), value);
            Add(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r, value);
            tree_[v] = tree_[v << 1] + tree_[v << 1 | 1];
        }

        int size_;
        std::vector<int64_t> tree_, add_, push_;
    };
}


namespace FenwickTree {
    struct BitTree { // Fenwick BitTree
        explicit BitTree(std::vector<int64_t> &a) : size_(a.size()), tree_(size_ + 1), data_(a) {
            for (int i = 0; i < size_; ++i) { increase(i + 1, a[i]); }
        };

        void increase(size_t i, int64_t x) {
            for (; i <= size_; i += F(i)) { tree_[i] += x; }
        }

        void update(size_t i, int64_t x) {
            increase(i, x - data_[i - 1]);
            data_[i - 1] = x;
        }

        int64_t sum(size_t l, size_t r) {
            return sum(r) - sum(l - 1);
        }

    private:
        size_t size_{};
        std::vector<int64_t> tree_, &data_;

        int64_t sum(int r) {
            int64_t result = 0;
            for (; r > 0; r -= F(r)) { result += tree_[r]; }
            return result;
        }

        static inline int64_t F(int64_t x) { return x & -x; }
    };
}


namespace Treap {
    template<class T>
    T GeneratePriority() {
        static std::mt19937 Generator(1337);
        return std::uniform_int_distribution<T>()(Generator);
    };


    class ImpTTreap { // Implicit Treap with segment operations, reverse, remove
    public:
        void Insert(int key, int value) {
            assert(0 <= key);
            assert(key <= (int) Nodes_.size());
            if (freeCells.empty()) {
                freeCells.push((int) Nodes_.size());
                Nodes_.emplace_back();
            }
            int freeIndex = freeCells.front();
            freeCells.pop();
            auto &newNode = Nodes_[freeIndex];
            newNode = TTreapNode(value);
            auto [left, right] = Split(Root_, key - 1);
            Root_ = Merge(left, Merge(freeIndex, right));
        }

        void Remove(int key) {
            assert(0 <= key);
            assert(key < (int) Nodes_.size());
            auto [left, right] = Split(Root_, key - 1);
            auto [keyTree, newRight] = Split(right, 0);
            Root_ = Merge(left, newRight);
            freeCells.push(keyTree);
        }

        int GetMin(int l, int r) {
            assert(0 <= l && l <= r && r < (int) Nodes_.size());
            auto [left, middleRight] = Split(Root_, l - 1); // [0 l - 1] [l n]
            auto [middle, right] = Split(middleRight, r - l); // [l r] [r + 1 n]
            int res = Nodes_[middle].Min;
            Root_ = Merge(left, Merge(middle, right));
            return res;
        }

        int GetMax(int l, int r) {
            assert(0 <= l && l <= r && r < (int) Nodes_.size());
            auto [left, middleRight] = Split(Root_, l - 1); // [0 l - 1] [l n]
            auto [middle, right] = Split(middleRight, r - l); // [l r] [r + 1 n]
            int res = Nodes_[middle].Max;
            Root_ = Merge(left, Merge(middle, right));
            return res;
        }

        void Reverse(int l, int r) {
            assert(0 <= l && l <= r && r < (int) Nodes_.size());
            auto [left, middleRight] = Split(Root_, l - 1); // [0 l - 1] [l n]
            auto [middle, right] = Split(middleRight, r - l); // [l r] [r + 1 n]
            Nodes_[middle].Reverse ^= true;
            Root_ = Merge(left, Merge(middle, right));
        }

        void PushBack(int value) {
            if (freeCells.empty()) {
                Nodes_.emplace_back();
                freeCells.push((int) Nodes_.size() - 1);
            }
            int freeIndex = freeCells.front();
            freeCells.pop();
            auto &newNode = Nodes_[freeIndex];
            newNode = TTreapNode(value);
            Root_ = Merge(Root_, freeIndex);
        }

        int Get(int key) {
            assert(0 <= key);
            assert(key < (int) Nodes_.size());
            int current = Root_;
            Push(current);
            while (true) {
                int currentKey = GetCount(Nodes_[current].Left);
                if (key == currentKey) {
                    return Nodes_[current].Value;
                }
                if (key < currentKey) {
                    current = Nodes_[current].Left;

                } else {
                    key -= (currentKey + 1);
                    current = Nodes_[current].Right;
                }
                Push(current);
            }
        }

        void MoveToFront(int l, int r) {
            assert(0 <= l && l <= r && r < (int) Nodes_.size());
            if (l == 0) { return; }
            auto [left, middleRight] = Split(Root_, l - 1); // [0 l - 1] [l n]
            auto [middle, right] = Split(middleRight, r - l); // [l r] [r + 1 n]
            Root_ = Merge(middle, Merge(left, right));
        }

        size_t Size() const {
            return Nodes_.size() - freeCells.size();
        }

    private:
        struct TTreapNode {
            int Count, Value, Priority, Left, Right, Min, Max;
            bool Reverse;

            explicit TTreapNode(int value = 0) :
                    Count(1), Value(value), Priority(GeneratePriority<int>()),
                    Left(-1), Right(-1), Reverse(false), Min(value), Max(value) {};
        };

        int Root_ = -1;
        std::vector<TTreapNode> Nodes_;
        std::queue<int> freeCells;

        int GetCount(int root) const {
            return root == -1 ? 0 : Nodes_[root].Count;
        }

        void UpdateCount(int root) {
            Nodes_[root].Count = 1 + GetCount(Nodes_[root].Left) + GetCount(Nodes_[root].Right);
        }

        void PushMinMax(int current) {
            Nodes_[current].Min = Nodes_[current].Value;
            Nodes_[current].Max = Nodes_[current].Value;
            if (Nodes_[current].Left != -1) { // Min/Max update
                Nodes_[current].Min = std::min(Nodes_[current].Min, Nodes_[Nodes_[current].Left].Min);
                Nodes_[current].Max = std::max(Nodes_[current].Max, Nodes_[Nodes_[current].Left].Max);
            }
            if (Nodes_[current].Right != -1) {
                Nodes_[current].Min = std::min(Nodes_[current].Min, Nodes_[Nodes_[current].Right].Min);
                Nodes_[current].Max = std::max(Nodes_[current].Max, Nodes_[Nodes_[current].Right].Max);
            }
        }

        void Push(int current) {
            if (current == -1) { return; }
            PushMinMax(current);
            if (!Nodes_[current].Reverse) { return; } // Reverse update
            Nodes_[current].Reverse = false;
            std::swap(Nodes_[current].Left, Nodes_[current].Right);
            if (Nodes_[current].Left != -1) { Nodes_[Nodes_[current].Left].Reverse ^= true; }
            if (Nodes_[current].Right != -1) { Nodes_[Nodes_[current].Right].Reverse ^= true; }
        }

        std::pair<int, int> Split(int current, int key) {
            if (current == -1) { return {-1, -1}; }
            Push(current);
            int currentKey = GetCount(Nodes_[current].Left);
            if (currentKey <= key) {
                key -= (currentKey + 1);
                auto [rightLeft, rightRight] = Split(Nodes_[current].Right, key);
                Nodes_[current].Right = rightLeft;
                UpdateCount(current);
                Push(current);
                return {current, rightRight};
            }
            auto [leftLeft, leftRight] = Split(Nodes_[current].Left, key);
            Nodes_[current].Left = leftRight;
            UpdateCount(current);
            Push(current);
            return {leftLeft, current};
        }

        int Merge(int left, int right) {
            if (left == -1) { return right; }
            if (right == -1) { return left; }
            Push(left);
            Push(right);
            if (Nodes_[left].Priority >= Nodes_[right].Priority) {
                Nodes_[left].Right = Merge(Nodes_[left].Right, right);
                UpdateCount(left);
                Push(left);
                return left;
            }
            Nodes_[right].Left = Merge(left, Nodes_[right].Left);
            UpdateCount(right);
            Push(right);
            return right;
        }
    };


    template<class T>
    struct TTreap { // Treap
        void Insert(int key) {
            auto [leftMid, right] = Split(Root_, key);
            auto [left, middle] = Split(leftMid, key - 1);
            if (middle == -1) {
                Nodes_.emplace_back();
                auto &newNode = Nodes_.back();
                newNode.Key = key;
                newNode.Priority = GeneratePriority<int>();
                newNode.Left = newNode.Right = -1;
                middle = Nodes_.size() - 1;
            }
            Root_ = Merge(left, Merge(middle, right));
        };

        std::optional<int> FindLowerBound(int key) {
            int result = -1, current = Root_;
            while (current >= 0) {
                if (Nodes_[current].Key >= key) {
                    result = current;
                    current = Nodes_[current].Left;
                } else {
                    current = Nodes_[current].Right;
                }
            }
            return result == -1 ? std::nullopt : std::optional<int>(Nodes_[result].Key);
        }

        bool Find(int key) const {
            auto [leftMid, right] = Split(Root_, key);
            auto [left, middle] = Split(leftMid, key - 1);
            bool result = (middle != -1);
            Root_ = Merge(left, Merge(middle, right));
            return result;
        };

    private:
        struct Node {
            T Key;
            int Priority, Left, Right;
        };

        int Root_ = -1;
        std::vector<Node> Nodes_;

        std::pair<int, int> Split(int current, int key) {
            if (current == -1) { return {-1, -1}; }
            if (Nodes_[current].Key <= key) {
                auto [left, right] = Split(Nodes_[current].Right, key);
                Nodes_[current].Right = left;
                return {current, right};
            }
            auto [left, right] = Split(Nodes_[current].Left, key);
            Nodes_[current].Left = right;
            return {left, current};
        };

        int Merge(int left, int right) {
            if (left == -1) { return right; }
            if (right == -1) { return left; }
            if (Nodes_[left].Priority >= Nodes_[right].Priority) {
                Nodes_[left].Right = Merge(Nodes_[left].Right, right);
                return left;
            }
            Nodes_[right].Left = Merge(left, Nodes_[right].Left);
            return right;
        };
    };
}

