#ifndef SGF_RANDOM_HPP
#define SGF_RANDOM_HPP

#include <random>

namespace sgf
{

class random
{
public:
    random() = delete;

    template <typename T>
    static T range(T min, T max)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(engine());
        }
        else
        {
            using CommonT = std::conditional_t<(sizeof(T) < sizeof(short)), int, T>;
            std::uniform_int_distribution<CommonT> dist(static_cast<CommonT>(min), static_cast<CommonT>(max));
            return static_cast<T>(dist(engine()));
        }
    }

    template <typename T = float>
    static T value()
    {
        return range<T>(static_cast<T>(0), static_cast<T>(1));
    }

    static bool chance(float p)
    {
        return value<float>() <= p;
    }

private:
    static std::mt19937 &engine()
    {
        static thread_local std::mt19937 gen(std::random_device{}());
        return gen;
    }
};

} // namespace sgf

#endif