#ifndef SGF_GAME_OBJECT_HPP
#define SGF_GAME_OBJECT_HPP

#include "../base/renderer.hpp"
#include "../type/position.hpp"
#include "../type/size.hpp"
#include "../type/vec2.hpp"
#include <chrono>
#include <cstdint>

namespace sgf
{

struct transform
{
    type::world_position pos{0.0, 0.0};
    type::world_size size{0, 0};
    type::vec2f pivot{0.5f, 0.5f};
    float rotation{0.0f};
    float scale{1.0f};
};

class game_object
{
public:
    explicit game_object(std::uint32_t id) : p_id(id) {}
    virtual ~game_object() = default;

    game_object(const game_object &)            = delete;
    game_object &operator=(const game_object &) = delete;

    virtual void on_init() = 0;
    virtual void on_update(std::chrono::nanoseconds dt) {};
    virtual void on_render(base::renderer &) {};

    std::uint32_t id() const noexcept
    {
        return p_id;
    }

    struct transform &transform() noexcept
    {
        return p_tf;
    }

    const struct transform &transform() const noexcept
    {
        return p_tf;
    }

    type::world_position &position() noexcept
    {
        return p_tf.pos;
    }

    const type::world_position &position() const noexcept
    {
        return p_tf.pos;
    }

    type::world_size &size() noexcept
    {
        return p_tf.size;
    }

    const type::world_size &size() const noexcept
    {
        return p_tf.size;
    }

    float &rotation() noexcept
    {
        return p_tf.rotation;
    }

    const float &rotation() const noexcept
    {
        return p_tf.rotation;
    }

    type::vec2f &pivot() noexcept
    {
        return p_tf.pivot;
    }

    const type::vec2f &pivot() const noexcept
    {
        return p_tf.pivot;
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
    bool active{true};
    bool should_remove{false};

private:
    std::uint32_t p_id;
    struct transform p_tf;
};

}; // namespace sgf

#endif