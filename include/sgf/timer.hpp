#ifndef SGF_TIMER_HPP
#define SGF_TIMER_HPP

#include <chrono>
#include <functional>

namespace sgf
{

class timer
{
public:
    using duration_t = std::chrono::nanoseconds;

    timer() = default;

    void start()
    {
        current     = duration_t::zero();
        has_invoked = false;
    }

    void start(const std::function<void()> &func)
    {
        callback = func;
        start();
    }

    template <typename Rep, typename Period>
    void update(std::chrono::duration<Rep, Period> delta_time)
    {
        if (has_invoked || !callback)
            return;

        current += std::chrono::duration_cast<duration_t>(delta_time);

        if (current >= target)
        {
            callback();
            has_invoked = true;
        }
    }

    template <typename Rep, typename Period>
    void set_time(std::chrono::duration<Rep, Period> time_span)
    {
        target = std::chrono::duration_cast<duration_t>(time_span);
    }

    void set_callback(const std::function<void()> &func)
    {
        callback = func;
    }

private:
    duration_t target{duration_t::zero()};
    duration_t current{duration_t::zero()};
    bool has_invoked{false};
    std::function<void()> callback{nullptr};
};

} // namespace sgf

#endif