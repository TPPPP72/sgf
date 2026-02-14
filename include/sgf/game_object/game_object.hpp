#ifndef SGF_GAME_OBJECT_HPP
#define SGF_GAME_OBJECT_HPP

#include "../base/renderer.hpp"
#include "../type/position.hpp"
#include "../type/size.hpp"
#include <chrono>
#include <cstdint>

namespace sgf
{

class game_object
{
public:
    explicit game_object(std::uint32_t id) : p_id(id) {}
    virtual ~game_object() = default;

    game_object(const game_object &)            = delete;
    game_object &operator=(const game_object &) = delete;

    virtual void on_init()                              = 0;
    virtual void on_update(std::chrono::nanoseconds dt) = 0;
    virtual void on_render(base::renderer &) const      = 0;

    std::uint32_t id() const noexcept
    {
        return p_id;
    }

    bool is_active() const noexcept
    {
        return active;
    }

    void set_active(bool state)
    {
        active = state;
    }

    bool is_pending_destruction() const noexcept
    {
        return should_remove;
    }

    void destroy()
    {
        should_remove = true;
    }

protected:
    type::world_position position;
    type::world_size size;
    bool active{true};
    bool should_remove{false};

private:
    std::uint32_t p_id;
};

}; // namespace sgf

#endif