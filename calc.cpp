#include <bits/stdc++.h>


namespace Comb {

int64_t mod = 1000000007;

int64_t fac64(int64_t x) {
    static const int64_t table[] = { // all factorials that fit into int64
            1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200,
            1307674368000, 20922789888000, 355687428096000, 6402373705728000, 121645100408832000,
            2432902008176640000
    };
    assert(x >= 0);
    assert(x <= 20);
    return table[x];
}

int64_t fac32(int64_t x) { // factorials mod 1000000007 (from 0! to 200!)
    static const int64_t table[] = {
            1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 227020758, 178290591,
            674358851, 789741546, 425606191, 660911389, 557316307, 146326063, 72847302, 602640637, 860734560,
            657629300, 440732388, 459042011, 394134213, 35757887, 36978716, 109361473, 390205642, 486580460,
            57155068, 943272305, 14530444, 523095984, 354551275, 472948359, 444985875, 799434881, 776829897,
            626855450, 954784168, 10503098, 472639410, 741412713, 846397273, 627068824, 726372166, 318608048,
            249010336, 948537388, 272481214, 713985458, 269199917, 75195247, 286129051, 595484846, 133605669,
            16340084, 996745124, 798197261, 286427093, 331333826, 536698543, 422103593, 280940535, 103956247,
            172980994, 108669496, 715534167, 518459667, 847555432, 719101534, 932614679, 878715114, 661063309,
            562937745, 472081547, 766523501, 88403147, 249058005, 671814275, 432398708, 753889928, 834533360,
            604401816, 187359437, 674989781, 749079870, 166267694, 296627743, 586379910, 119711155, 372559648,
            765725963, 275417893, 990953332, 104379182, 437918130, 229730822, 432543683, 551999041, 407899865,
            829485531, 925465677, 24826746, 681288554, 260451868, 649705284, 117286020, 136034149, 371858732,
            391895154, 67942395, 881317771, 114178486, 473061257, 294289191, 314702675, 79023409, 640855835,
            825267159, 333127002, 640874963, 750244778, 281086141, 979025803, 294327705, 262601384, 400781066,
            903100348, 112345444, 54289391, 329067736, 753211788, 190014235, 221964248, 853030262, 424235847,
            817254014, 50069176, 159892119, 24464975, 547421354, 923517131, 757017312, 38561392, 745647373,
            847105173, 912880234, 757794602, 942573301, 156287339, 224537377, 27830567, 369398991, 365040172,
            41386942, 621910678, 127618458, 674190056, 892978365, 448450838, 994387759, 68366839, 417262036,
            100021558, 903643190, 619341229, 907349424, 64099836, 89271551, 533249769, 318708924, 92770232,
            420330952, 818908938, 584698880, 245797665, 489377057, 66623751, 192146349, 354927971, 661674180,
            71396619, 351167662, 19519994, 689278845, 962979640, 929109959, 389110882, 98399701, 89541861,
            460662776, 289903466, 110982403, 974515647, 928612402, 722479105
    };
    assert(x >= 0);
    assert(x <= 200);
    return table[x];
}

int64_t pow(int64_t a, int64_t b) { // fast pow
    assert(b >= 0);
    if (!b) { return 1; }
    int64_t m = pow(a, b >> 1);
    m = (m * m) % mod;
    if (b & 1) { m = (m * a) % mod; }
    return m;
}

int64_t inv(int64_t x) { // multiply invariant
    return pow(x, mod - 2);
}

int64_t nCr(int64_t n, int64_t r) { // combinations
    assert(n >= r);
    int64_t n1 = fac32(n), d1 = inv(fac32(n - r)), d2 = inv(fac32(r));
    d1 = (d1 * d2) % mod;
    return (n1 * d1) % mod;
}

}; // Comb


namespace Matrix {

int64_t mod = 1000000007;
const int size_ = 2;

class Matrix {
public:
    int64_t data[size_][size_];

    void clear() { memset(data, 0, sizeof(data)); }

    void to_one() { data[0][0] = data[1][1] = 1; data[1][0] = data[0][1] = 0; }

    Matrix operator+(const Matrix& other) const {
        Matrix result{};
        result.clear();
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                result.data[i][j] = (data[i][j] + other.data[i][j]) % mod;
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result{};
        result.clear();
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                for (int k = 0; k < size_; ++k) {
                    result.data[i][k] += (1LL * data[i][j] * other.data[j][k]);
                    result.data[i][k] %= mod;
                }
            }
        }
        return result;
    }

    Matrix power(int64_t n) {
        Matrix result{}, temp = *this;
        result.to_one();
        for (; n > 0; n >>= 1) {
            if (n & 1) { result = result * temp; }
            temp = temp * temp;
        }
        return result;
    }
};

}; // Matrix


namespace Primes {

constexpr int MAX = (1 << 16);
typedef uint32_t prime_type;

bool is_prime[MAX + 1];
std::vector<prime_type> primes;

void init() {
    static bool initialized = false;
    if (initialized) { return; }
    initialized = true;

    for (auto& x : is_prime) {
        x = true;
    }
    is_prime[0] = is_prime[1] = false;
    for (prime_type i = 2; i * i <= MAX; ++i) {
        if (is_prime[i]) {
            for (prime_type k = i * i; k <= MAX; k += i) {
                is_prime[k] = false;
            }
        }
    }
    for (prime_type i = 2; i <= MAX; ++i) {
        if (is_prime[i]) { primes.push_back(i); }
    }
}

prime_type gen_prime_divs(prime_type n) {
    static prime_type value = n, last_used{};
    static auto it = primes.begin();
    if (last_used != n) { last_used = value = n; it = primes.begin(); }
    for (; it != primes.end() && *it <= value; ) {
        while (value % *it == 0) { value /= *it; return *it; }
        ++it;
    }
    it = primes.end();
    return (value != 1 ? value : 0);
}

prime_type gen_unique_prime_divs(prime_type n) {
    static prime_type value = n, last_used{};
    static auto it = primes.begin();
    if (last_used != n) { last_used = value = n; it = primes.begin(); }
    for (; it != primes.end() && *it <= value; ++it) {
        prime_type res{};
        if (value % *it == 0) { res = *it; }
        while (value % *it == 0) { value /= *it; }
        if (res) { return res; }
    }
    it = primes.end();
    return (value != 1 ? value : 0);
}

std::vector<prime_type> get_prime_divs(prime_type n) {
    std::vector<prime_type> res;
    for (const auto& x : primes) {
        if (x * x > n) { break; }
        while (n % x == 0) {
            res.push_back(x);
            n /= x;
        }
    }
    if (n != 1) {
        res.push_back(n);
    }
    return res;
}

}; // Primes


class Bit {
public:
Bit() = default;
Bit(uint64_t x) : x(x) {};

template<class Os>
friend Os& operator << (Os& ostream, const Bit& bit) { ostream << bit.x; return ostream; }

template<class Is>
friend Is& operator >> (Is& istream, Bit& bit) { istream >> bit.x; return istream; }

inline uint64_t operator | (const Bit& other) const { return x | other.x; }
inline uint64_t operator & (const Bit& other) const { return x & other.x; }
inline uint64_t operator ^ (const Bit& other) const { return x ^ other.x; }
inline uint64_t& operator |= (const Bit& other) { x |= other.x; return x; }
inline uint64_t& operator &= (const Bit& other) { x &= other.x; return x; }
inline uint64_t& operator ^= (const Bit& other) { x ^= other.x; return x; }
inline uint64_t operator ~ () const { return (~x) & (uint64_t(-1) >> (1 + __builtin_clzll(x))); }

inline bool operator != (const Bit& other) const { return x != other.x; }
inline bool operator == (const Bit& other) const { return x == other.x; }
inline bool operator <= (const Bit& other) const { return x <= other.x; }
inline bool operator >= (const Bit& other) const { return x >= other.x; }
inline bool operator < (const Bit& other) const { return x < other.x; }
inline bool operator > (const Bit& other) const { return x > other.x; }

inline uint16_t operator[] (uint16_t index) const { return x >> index & 1; }

inline void set(uint16_t index, uint16_t value) { x = (x & (uint64_t(-1) ^ (1 << index))) | (value << index); }
inline uint16_t get(uint16_t index) const { return x >> index & 1; }

inline void set(uint16_t left, uint16_t right, uint16_t value) {
    x &= (uint64_t(-1) << (right + 1)) | (uint64_t(-1) >> (64 - left));
    if (value) { x |= ~(uint64_t(-1) << (right + 1)) | (uint64_t(-1) >> (64 - left)); }
}

inline uint64_t get(uint16_t left, uint16_t right) const {
    return (x << (63 - right) >> (63 - right + left));
}

std::string str() const {
    std::string result;
    for (int i = 63 - __builtin_clzll(x); i >= 0; --i) {
        result += (x >> i & 1) + '0';
    }
    return result;
}

operator uint64_t () const { return x; }
operator int64_t () const { return int64_t(x); }
operator std::string () const { return str(); }
operator bool () const { return bool(x); }

inline uint16_t topbit() const { return 63 - __builtin_clzll(x); }
inline uint16_t lowbit() const { return  __builtin_ctzll(x); }
inline uint16_t popcnt() const { return __builtin_popcountll(x); }

private:
uint64_t x;
};
