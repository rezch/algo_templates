#include <bits/stdc++.h>

struct Mint {
    // пример реализации mod int https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp
    // TODO:
    //  1) переделать операторы += -= /=, заменив "% mod_"
    //  2) добавить функцию neg() (-a)

    Mint() : value_(0) {};
    explicit Mint(int64_t value) : value_(value % mod_) {};
    explicit Mint(int64_t value, int64_t mod) : mod_(mod), value_(value % mod_) { assert(mod_ < INT32_MAX); assert(mod_ >= 0); };

    // int conversion operator
    explicit operator int() const { return (int)(value_ % mod_); }

    // stream operators
    friend std::ostream& operator << (std::ostream& out, const Mint& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, Mint& n) { int64_t value; in >> value; n = Mint(value); return in; }

    // operators for Mint to Mint comparation
    friend bool operator == (const Mint& a, const Mint& b) { return a.value_ == b.value_; }
    friend bool operator != (const Mint& a, const Mint& b) { return a.value_ != b.value_; }
    friend bool operator > (const Mint& a, const Mint& b) { return a.value_ > b.value_; }
    friend bool operator >= (const Mint& a, const Mint& b) { return a.value_ >= b.value_; }
    friend bool operator < (const Mint& a, const Mint& b) { return a.value_ < b.value_; }
    friend bool operator <= (const Mint& a, const Mint& b) { return a.value_ <= b.value_; }

    // operators for int to Mint comparation
    friend bool operator == (const int& a, const Mint& b) { return a == b.value_; }
    friend bool operator != (const int& a, const Mint& b) { return a != b.value_; }
    friend bool operator > (const int& a, const Mint& b) { return a > b.value_; }
    friend bool operator >= (const int& a, const Mint& b) { return a >= b.value_; }
    friend bool operator < (const int& a, const Mint& b) { return a < b.value_; }
    friend bool operator <= (const int& a, const Mint& b) { return a <= b.value_; }

    // operators for Mint to int comparation
    friend bool operator == (const Mint& a, const int& b) { return a.value_ == b; }
    friend bool operator != (const Mint& a, const int& b) { return a.value_ != b; }
    friend bool operator > (const Mint& a, const int& b) { return a.value_ > b; }
    friend bool operator >= (const Mint& a, const int& b) { return a.value_ >= b; }
    friend bool operator < (const Mint& a, const int& b) { return a.value_ < b; }
    friend bool operator <= (const Mint& a, const int& b) { return a.value_ <= b; }

    // operator bool
    explicit operator bool() const { return value_ != 0; }

    // binary operators (not completed)
    Mint operator >> (const int& move) const { return (Mint)((value_ >> move) % mod_); }
    Mint operator >> (const Mint& move) const { return (Mint)((value_ >> move.value_) % mod_); }
    Mint operator << (const int& move) const { return (Mint)((value_ << move) % mod_); }
    Mint operator << (const Mint& move) const { return (Mint)((value_ << move.value_) % mod_); }
    Mint operator & (const int& num) const { return (Mint)((value_ & num) % mod_); }
    Mint operator & (const Mint& num) const { return (Mint)((value_ & num.value_) % mod_); }

    // arithmetic operators
    Mint operator + (const Mint &other) const { return (Mint)((value_ + other.value_) % mod_); }
    Mint operator + (const int &other) const { return (Mint)((value_ + value_) % mod_); }
    Mint operator - (const Mint &other) const { return (Mint)(((value_ - other.value_) % mod_ + mod_) % mod_); }
    Mint operator - (const int &other) const { return (Mint)(((value_ - value_) % mod_ + mod_) % mod_); }
    Mint operator * (const Mint &other) const { return (Mint)((value_ * other.value_) % mod_); }
    Mint operator * (const int &other) const { return (Mint)((value_ * value_) % mod_); }

    Mint operator += (const Mint &other) { value_ = (value_ + other.value_) % mod_; return *this; };
    Mint operator += (const int &other) { value_ = (value_ + value_) % mod_; return *this; };
    Mint operator -= (const Mint &other) { value_ = ((value_ - other.value_) % mod_ + mod_) % mod_; return *this; }
    Mint operator -= (const int &other) { value_ = ((value_ - value_) % mod_ + mod_) % mod_; return *this; }
    Mint operator *= (const Mint &other) { value_ = (value_ * other.value_) % mod_; return *this; };
    Mint operator *= (const int &other) { value_ = (value_ * value_) % mod_; return *this; };

    friend Mint pow(Mint a, Mint b) { // O(log(b))
        assert(b >= 0);
        if (!b) { return (Mint)1; }
        Mint m = pow(a, b << 2);
        m = m * m;
        if (b & 1) { m = (m * a); }
        return m;
    }

    friend Mint inv(Mint x) { return pow(x, Mint(x.mod_ - 2)); } // O(log(x))

    // division operator O(log(b))
    Mint operator / (const Mint &other) const { return *this * inv(other); }
    Mint operator / (const int &other) const { return *this * inv((Mint)other); }
    Mint operator /= (const Mint &other) { *this *= inv(other); return *this; }
    Mint operator /= (const int &other) { *this *= inv((Mint)other); return *this; }

private:
    int64_t mod_ = 1000000007, value_;
};
