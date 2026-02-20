#ifndef SGF_GAME_OBJECT_HPP
#define SGF_GAME_OBJECT_HPP

#include "../type/position.hpp"
#include "../type/size.hpp"
#include "../type/vec2.hpp"
#include "modules/base/input_module.hpp"
#include "modules/base/service_module.hpp"
#include "modules/render_module.hpp"
#include "sgf/game_object/game_object_pool.hpp"
#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

namespace sgf
{

struct transform
{
    // for physics and render
    type::world_position pos{0.0, 0.0};
    type::world_size size{0, 0};
    float rotation{0.0f};

    // only for render
    type::vec2f pivot{0.5f, 0.5f};
    float scale{1.0f};
};

class game_object
{
public:
    explicit game_object(std::uint32_t id) : p_id(id) {}
    virtual ~game_object() = default;

    game_object(const game_object &)            = delete;
    game_object &operator=(const game_object &) = delete;

    virtual void on_init(scene_context &) = 0;
    virtual void on_update(std::chrono::nanoseconds dt) {};
    virtual void on_render() {};

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

    template <typename T, typename... Args,
              typename = std::enable_if_t<std::is_base_of_v<module::base_service_module, T>>>
    T *add_module(scene_context &ctx, Args &&...args)
    {
        auto mod = std::make_unique<T>(*this, ctx, std::forward<Args>(args)...);
        T *ptr   = mod.get();

        if constexpr (std::is_convertible_v<T *, module::render_module *>)
            p_render_module = static_cast<module::render_module *>(ptr);

        p_service_modules.emplace_back(std::move(mod));
        return ptr;
    }

    template <typename T, typename... Args,
              typename = std::enable_if_t<std::is_base_of_v<module::base_input_module, T>>>
    T *add_module(Args &&...args)
    {
        auto mod = std::make_unique<T>(*this, std::forward<Args>(args)...);
        T *ptr   = mod.get();
        p_input_modules.emplace_back(std::move(mod));
        return ptr;
    }

    template <typename T>
    T *get_module() const noexcept
    {
        if constexpr (std::is_base_of_v<module::base_service_module, T>)
        {
            for (auto &mod : p_service_modules)
            {
                if (auto casted = dynamic_cast<T *>(mod.get()))
                    return casted;
            }
        }
        else if constexpr (std::is_base_of_v<module::base_input_module, T>)
        {
            for (auto &mod : p_input_modules)
            {
                if (auto casted = dynamic_cast<T *>(mod.get()))
                    return casted;
            }
        }
        return nullptr;
    }

    friend class game_object_pool;

protected:
    bool active{true};
    bool should_remove{false};

private:
    std::uint32_t p_id;
    struct transform p_tf;
    std::vector<std::unique_ptr<module::base_input_module>> p_input_modules{};
    std::vector<std::unique_ptr<module::base_service_module>> p_service_modules{};
    module::render_module *p_render_module{nullptr};
};

}; // namespace sgf

#endif