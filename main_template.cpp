#pragma GCC optimize ("Ofast,unroll-loops")
#ifndef UwU
#endif

#include <bits/stdc++.h>

#define timer(func, ...) { \
        auto start_time_inner = std::chrono::steady_clock::now(); \
        (func)(__VA_ARGS__);            \
        auto end_time_inner = std::chrono::steady_clock::now();   \
        auto elapsed_ns_inner = std::chrono::duration_cast<std::chrono::milliseconds> \
        (end_time_inner - start_time_inner); \
        std::cout << "Time elapsed: " << elapsed_ns_inner.count() << " ms\n";                                 \
        }
#define test(test_count, func, ...) { \
        for (int i_inner = 0; i_inner < (test_count); ++i_inner) { \
            timer((func), __VA_ARGS__);        \
        }}
#define ifout(statement, ok_msg, other_msg) {                \
        if (statement) { std::cout << (ok_msg) << std::endl; } \
        else { std::cout << (other_msg) << std::endl; } }
#define solve_t(func) { \
        int t_inner; in >> t_inner;      \
        for (int i_inner = 0; i_inner < t_inner; ++i_inner) { (func)(); }}
#define fast std::cin.tie(0); \
        std::cout.tie(0); \
        std::ios_base::sync_with_stdio(0);
#define rrng(var, from, to) \
        for (int (var) = (from); (var) >= (to); --(var))
#define arng(var, from, to) \
        for (int (var) = (from); (var) < (to); ++(var))
#define mrng(vara, varb, ind1, ind2) \
        rng((vara), (ind1)) rng((varb), (ind2))
#define iter(var, list) \
        for (auto& (var) : (list))
#define rng(var, to) \
        arng((var), 0, (to))
#define clr(list, size) std::memset(&(list), 0, sizeof((list)[0]) * (size));
#define input(list) iter((var), (list)) { std::cin >> (var); }
#define precision(n) std::fixed << std::setprecision((n))
#define sort_(list) std::sort((list).begin(), (list).end())
#define writef(filename) freopen((filename), "w", stdout);
#define readf(filename) freopen((filename), "r", stdin);
#define ret(x) std::cout << (x) << std::endl; return;
#define rall(list) (list).rbegin(), (list).rend()
#define retn std::cout << std::endl; return;
#define all(list) (list).begin(), (list).end()
#define lcm(x, y) ((x) * (y) / std::__gcd((x), (y)))
#define gcd(x, y) std::__gcd((x), (y))
#define sw(a, b) std::swap((a), (b));
#define cauto const auto&
#define mp std::make_pair
#define eb emplace_back
#define out std::cout
#define nl std::endl
#define pb push_back
#define in std::cin

template <class T> bool set_max(T& a, T b)
{ { if (a >= b) return false; } { a = b; return true; } }
template <class T> bool set_min(T& a, T b)
{ { if (a <= b) return false; } { a = b; return true; } }

int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); } // 0 -> -1
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); } // 0 -> -1
int popcnt(int x) { return __builtin_popcount(x); }
template <typename T, typename U> T ceil(T x, U y)
{ return (x > 0 ? (x + y - 1) / y : x / y); }
template <typename T, typename U> T floor(T x, U y)
{ return (x > 0 ? x / y : (x - y + 1) / y); }

template <class T, class U> using umtt = std::unordered_map<T, U>;
template <class T> using vvt = std::vector<std::vector<T>>;
template <class T, class U> using ptt = std::pair<T, U>;
template <class T> using umt = std::unordered_map<T, T>;
template <class T> using mst = std::multiset<T>;
template <class T> using pt = std::pair<T, T>;
template <class T> using vt = std::vector<T>;
template <class T> using stk = std::stack<T>;
template <class T> using qt = std::queue<T>;
template <class T> using st = std::set<T>;
typedef std::string str;
typedef vt<pt<int>> vpi;
typedef vvt<int> vvi;
typedef vt<int> vi;
typedef pt<int> pi;

template <class T> void print(T& list, char splitter = ' ')
{ for (const auto& value : list) { std::cout << value << splitter; } std::cout << std::endl; }

void read() { }
template <class T> void read_(T& value) { std::cin >> value; }
template <class T, class... U> void read(T& head, U&... tail) { read_(head); read(tail...); }
#define rt(inner_type, ...) \
    inner_type __VA_ARGS__; read(__VA_ARGS__);

void write_() { std::cout << std::endl; }
void write() { std::cout << std::endl; }
template <class T> void W (T value) { std::cout << ' ' << value; }
template <class T, class...U> void write_(T head, U... tail) { W(head); write_(tail...);}
template <class T, class...U> void write(T head, U... tail) { std::cout << head; write_(tail...); }

template <class T> void set(int n, T value) {}
template <class T, class U> void set_(int n, T value, U& list) { list.assign(n, value); }
template <class T, class U, class... W> void set(int n, T value, U& head, W&... tail) {
    set_(n, value, head); set(n, value, tail...); };

// ------------------ SOLVE ------------------


void solve() {
    /* UwU */
}


signed main() {
    fast;

#ifdef UwU
    readf("input.in");
//    writef("output.out");
    test(1, solve);
#else
//    readf("unionday.in");
//    writef("unionday.out");
    solve();
#endif
    //solve_t(solve);

    return 0;
}
