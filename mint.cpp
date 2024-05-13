#include <bits/stdc++.h>

struct Mint {
    // mod int implementation example: https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp

    constexpr Mint() = default;
    constexpr explicit Mint(int64_t value) : value_(value % mod_) { value_ = (value_ < 0) ? value_ + mod_ : value_; };
    constexpr explicit Mint(int value) : Mint((int64_t)value) {};
    constexpr explicit Mint(int64_t value, int64_t mod) : value_(value), mod_(mod) { assert(0 < mod_ && mod_ < INT32_MAX); value_ = (value_ < 0) ? value_ + mod_ : value_; };
    constexpr explicit Mint(int value, int mod) : Mint((int64_t)value, (int64_t)mod) {};

    // int conversion operator
    constexpr explicit operator int() const { return (int)(value_); }

    // stream operators
    constexpr friend std::ostream& operator << (std::ostream& ostream, const Mint& n) { return ostream << int(n); }
    constexpr friend std::istream& operator >> (std::istream& istream, Mint& n) { int64_t value; istream >> value; n = Mint(value, n.mod_); return in; }

    // operators for comparation
    constexpr friend bool operator == (const Mint& a, const Mint& b) { return a.value_ == b.value_; }
    constexpr friend bool operator == (const int& a, const Mint& b) { return a == b.value_; }
    constexpr friend bool operator == (const Mint& a, const int& b) { return a.value_ == b; }
    constexpr friend bool operator != (const Mint& a, const Mint& b) { return a.value_ != b.value_; }
    constexpr friend bool operator != (const int& a, const Mint& b) { return a != b.value_; }
    constexpr friend bool operator != (const Mint& a, const int& b) { return a.value_ != b; }
    constexpr friend bool operator > (const Mint& a, const Mint& b) { return a.value_ > b.value_; }
    constexpr friend bool operator > (const int& a, const Mint& b) { return a > b.value_; }
    constexpr friend bool operator > (const Mint& a, const int& b) { return a.value_ > b; }
    constexpr friend bool operator >= (const Mint& a, const Mint& b) { return a.value_ >= b.value_; }
    constexpr friend bool operator >= (const int& a, const Mint& b) { return a >= b.value_; }
    constexpr friend bool operator >= (const Mint& a, const int& b) { return a.value_ >= b; }
    constexpr friend bool operator < (const Mint& a, const Mint& b) { return a.value_ < b.value_; }
    constexpr friend bool operator < (const int& a, const Mint& b) { return a < b.value_; }
    constexpr friend bool operator < (const Mint& a, const int& b) { return a.value_ < b; }
    constexpr friend bool operator <= (const Mint& a, const Mint& b) { return a.value_ <= b.value_; }
    constexpr friend bool operator <= (const int& a, const Mint& b) { return a <= b.value_; }
    constexpr friend bool operator <= (const Mint& a, const int& b) { return a.value_ <= b; }

    // operator bool
    constexpr explicit operator bool() const { return value_ != 0; }

    // binary operators
    constexpr friend Mint operator >> (const Mint& a, const int& move) { return Mint(a.value_ >> move, a.mod_); }
    constexpr friend Mint operator >> (const Mint& a, const Mint& move) { return Mint(a.value_ >> move.value_, a.mod_); }
    constexpr friend Mint operator >> (const int& a, const Mint& move) { return Mint((int64_t)a >> move.value_, move.mod_); }
    constexpr friend Mint operator << (const Mint& a, const int& move) { return Mint(a.value_ << move, a.mod_); }
    constexpr friend Mint operator << (const Mint& a, const Mint& move) { return Mint(a.value_ << move.value_, a.mod_); }
    constexpr friend Mint operator << (const int& a, const Mint& move) { return Mint((int64_t)a << move.value_, move.mod_); }
    constexpr friend Mint operator & (const Mint& a, const int& b) { return Mint(a.value_ & b, a.mod_); }
    constexpr friend Mint operator & (const Mint& a, const Mint& b) { return Mint(a.value_ & b.value_, a.mod_); }
    constexpr friend Mint operator & (const int& a, const Mint& b) { return Mint(a & b.value_, b.mod_); }
    constexpr friend Mint operator | (const Mint& a, const int& b) { return Mint(a.value_ | b, a.mod_); }
    constexpr friend Mint operator | (const Mint& a, const Mint& b) { return Mint(a.value_ | b.value_, a.mod_); }
    constexpr friend Mint operator | (const int& a, const Mint& b) { return Mint(a | b.value_, b.mod_); }
    constexpr friend Mint operator ^ (const Mint& a, const int& b) { return Mint(a.value_ ^ b, a.mod_); }
    constexpr friend Mint operator ^ (const Mint& a, const Mint& b) { return Mint(a.value_ ^ b.value_, a.mod_); }
    constexpr friend Mint operator ^ (const int& a, const Mint& b) { return Mint(a ^ b.value_, b.mod_); }
    constexpr friend Mint operator ~ (const Mint& a) { return Mint(~a.value_, a.mod_); }

    // arithmetic operators
    constexpr friend Mint operator + (const Mint& a, const Mint& b) { return Mint(a.value_ + b.value_, a.mod_); }
    constexpr friend Mint operator + (const Mint& a, const int& b) { return Mint(a.value_ + b, a.mod_); }
    constexpr friend Mint operator + (const int& a, const Mint& b) { return Mint(a + b.value_, b.mod_); }
    constexpr friend Mint operator - (const Mint& a, const Mint& b) { return Mint(a.value_ - b.value_, a.mod_); }
    constexpr friend Mint operator - (const Mint& a, const int& b) { return Mint(a.value_ - b, a.mod_); }
    constexpr friend Mint operator - (const int& a, const Mint& b) { return Mint(a - b.value_, b.mod_); }
    constexpr friend Mint operator * (const Mint& a, const Mint& b) { return Mint(a.value_ * b.value_, a.mod_); }
    constexpr friend Mint operator * (const Mint& a, const int& b) { return Mint(a.value_ * b, a.mod_); }
    constexpr friend Mint operator * (const int& a, const Mint& b) { return Mint(a * b.value_, b.mod_); }
    constexpr friend Mint operator / (const Mint& a, const Mint& b) { return Mint(a) /= b; }
    constexpr friend Mint operator / (const Mint& a, const int& b) { return Mint(a.value_ * b, a.mod_); }
    constexpr friend Mint operator / (const int& a, const Mint& b) { return Mint(a * b.value_, b.mod_); }

    constexpr Mint operator += (const Mint &other) {
        value_ -= mod_ - other.value_;
        value_ = (value_ < 0) ? value_ + mod_ : value_;
        return *this;
    }
    constexpr Mint operator += (const int &other) { return *this += Mint((int64_t)other, mod_); }
    constexpr Mint operator -= (const Mint &other) {
        value_ -= other.value_;
        value_ = (value_ < 0) ? value_ + mod_ : value_;
        return *this;
    }
    constexpr Mint operator -= (const int &other) { return *this -= Mint((int64_t)other, mod_); }
    constexpr Mint operator *= (const Mint &other) {
        value_ = value_ * other.value_ % mod_;
        return *this;
    }
    constexpr Mint operator *= (const int &other) { return *this *= Mint((int64_t)other, mod_); };
    constexpr Mint operator /= (const Mint &other) { return *this *= other.inv(); };
    constexpr Mint operator /= (const int &other) { return *this *= Mint((int64_t)other, mod_).inv(); };

    // fast pow function
    friend Mint pow(Mint a, Mint b) { // O(log(b))
        assert(b >= 0);
        if (!b) { return Mint((int64_t)1, a.mod_); }
        Mint m = pow(a, b << 2);
        m = m * m;
        if (b & 1) { m = (m * a); }
        return m;
    }
    friend Mint pow(Mint a, int b) { return pow(a, Mint((int64_t)b, a.mod_)); }
    friend Mint pow(int a, Mint b) { return pow(Mint((int64_t)a, b.mod_), b); }

    // get modular division invariant
    Mint inv() const { return pow(*this, Mint(mod_ - 2)); } // O(log(this))

    // returns
    Mint neg() const { return Mint(value_ ? mod_ - value_ : 0); }

private:
    int64_t value_{}, mod_ = 1000000007;
};
