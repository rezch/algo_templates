#ifndef LOCAL
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,bmi,bmi2")
#endif

#include <bits/stdc++.h>

#define fast std::cin.tie(0); \
        std::cout.tie(0); \
        std::ios_base::sync_with_stdio(0);
#define arng(var, from, to) \
        for (int var = from; var < to; ++var)
#define rng(var, to) \
        arng(var, 0, to)
#define iter(var, list) \
        for (auto& var : list)
#define mrng(vara, varb, ind1, ind2) \
        rng(vara, ind1) rng(varb, ind2)
#define prints(list, ostream) \
        iter(var, list) { ostream << var << ' '; } ostream << std::endl;
#define inputs(list, istream) iter(var, list) { istream >> var; }
#define print(list) \
        iter(var, list) { std::cout << var << ' '; } std::cout << std::endl;
#define input(list) iter(var, list) { std::cin >> var; }
#define pb push_back
#define all(list) list.begin(), list.end()
#define precision(n) std::fixed << std::setprecision(n)
#define gcd(x, y) std::__gcd(x, y)
#define lcm(x, y) (x * y / gcd(x, y))
#define nl std::endl
#define test(test_count, func, ...) { \
        for (int i = 0; i < test_count; ++i) { \
            func(__VA_ARGS__);        \
            std::cout << std::endl;   \
        }}
#define solve_t(func, in, out) { \
        int t; in >> t;      \
        for (int i = 0; i < t; ++i) { func(in, out); }}
#define clr(list, size) std::memset(&list, 0, sizeof(list[0]) * size);
#define sw(a, b) std::swap(a, b);
#define read(filename) freopen(filename, "r", stdin);
#define write(filename) freopen(filename, "w", stdout);
#define ret(x) std::cout << x << std::endl; return;

template <class T> bool set_max(T& a, T b) { { if (a >= b) return false; } { a = b; return true; } }
template <class T> bool set_min(T& a, T b) { { if (a <= b) return false; } { a = b; return true; } }

template <typename T, typename U> T ceil(T x, U y) { return (x > 0 ? (x + y - 1) / y : x / y); }
template <typename T, typename U> T floor(T x, U y) { return (x > 0 ? x / y : (x - y + 1) / y); }
int popcnt(int x) { return __builtin_popcount(x); }
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); } // 0 -> -1
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); } // 0 -> -1

template <class T> using vt = std::vector<T>;
template <class T> using vvt = std::vector<std::vector<T>>;
template <class T> using pt = std::pair<T, T>;
template <class T, class U> using ptt = std::pair<T, U>;
template <class T> using umt = std::unordered_map<T, T>;
template <class T, class U> using umtt = std::unordered_map<T, U>;
template <class T> using stt = std::set<T>;
template <class T> using mst = std::multiset<T>;
template <class T> using qt = std::queue<T>;
template <class T> using st = std::stack<T>;
typedef std::string str;
typedef vt<int> vi;
typedef vvt<int> vvi;

// ------------------ SOLVE ------------------


template <typename instream, typename outstream>
void solve(instream& in, outstream& out) {

}

signed main() {
    fast;

#ifndef ONLINE_JUDGE
    read("input.in");
    //write("output.out");
    //test(3, solve, std::cin, std::cout);
#else
    solve_t(solve, std::cin, std::cout);
    //test(1, solve, std::cin, std::cout);
#endif

    return 0;
}


