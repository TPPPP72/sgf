#ifndef SGF_BASE_VECTOR2_HPP
#define SGF_BASE_VECTOR2_HPP

#include <algorithm>
#include <cmath>

namespace sgf::type::base
{
template <typename T>
struct vector2
{
    static_assert(std::is_arithmetic_v<T>, "Vector2 only supports numeric types");

    vector2()  = default;
    ~vector2() = default;
    template <typename Tp, typename Up>
    vector2(Tp x, Up y)
    {
        this->x = x;
        this->y = y;
    }
    vector2(const vector2 &b)     = default;
    vector2(vector2 &&b) noexcept = default;
    vector2 operator+(const vector2 &b) const
    {
        return {this->x + b.x, this->y + b.y};
    }
    vector2 &operator+=(const vector2 &b)
    {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }
    vector2 operator+(T b) const
    {
        return {this->x + b, this->y + b};
    }
    vector2 &operator+=(T b)
    {
        this->x += b;
        this->y += b;
        return *this;
    }
    vector2 operator-(const vector2 &b) const
    {
        return {this->x - b.x, this->y - b.y};
    }
    vector2 &operator-=(const vector2 &b)
    {
        this->x -= b.x;
        this->y -= b.y;
        return *this;
    }
    vector2 operator-(T b) const
    {
        return {this->x - b, this->y - b};
    }
    vector2 &operator-=(T b)
    {
        this->x -= b;
        this->y -= b;
        return *this;
    }
    vector2 operator*(const vector2 &b) const
    {
        return {this->x * b.x, this->y * b.y};
    }
    vector2 &operator*=(const vector2 &b)
    {
        this->x *= b.x;
        this->y *= b.y;
        return *this;
    }
    vector2 operator*(T b) const
    {
        return {this->x * b, this->y * b};
    }
    vector2 &operator*=(T b)
    {
        this->x *= b;
        this->y *= b;
        return *this;
    }
    vector2 operator/(const vector2 &b) const
    {
        return {this->x / b.x, this->y / b.y};
    }
    vector2 &operator/=(const vector2 &b)
    {
        this->x /= b.x;
        this->y /= b.y;
        return *this;
    }
    vector2 operator/(T b) const
    {
        return {this->x / b, this->y / b};
    }
    vector2 &operator/=(T b)
    {
        this->x /= b;
        this->y /= b;
        return *this;
    }
    bool operator==(const vector2 &b) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            auto almost_equal = [](T a, T b) -> bool
            {
                if (a == b)
                    return true;

                T diff    = std::abs(a - b);
                T max_val = std::max(std::abs(a), std::abs(b));

                return diff <= T(1e-7) * max_val || diff <= T(1e-12);
            };

            return almost_equal(this->x, b.x) && almost_equal(this->y, b.y);
        }
        return (this->x == b.x && this->y == b.y);
    }
    bool operator!=(const vector2 &b) const
    {
        return (!((*this) == b));
    }
    vector2 &operator=(const vector2 &b)
    {
        this->x = b.x;
        this->y = b.y;
        return *this;
    }
    T x{0};
    T y{0};
};

template <typename Tp, typename Up>
vector2(Tp, Up) -> vector2<std::common_type_t<Tp, Up>>;
} // namespace sgf::type::base

#endif