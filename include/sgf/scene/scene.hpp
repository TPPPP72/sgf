#ifndef SGF_SCENE_HPP
#define SGF_SCENE_HPP

#include <cstdint>

namespace sgf
{

namespace base
{
class renderer;
}

class input_event;
class frame_context;

class scene
{
public:
    explicit scene(std::uint32_t id) : p_id(id) {}
    virtual ~scene() = default;

    scene(const scene &)            = delete;
    scene &operator=(const scene &) = delete;

    virtual void on_init()                        = 0;
    virtual void on_input(const input_event &)    = 0;
    virtual void on_update(const frame_context &) = 0;
    virtual void on_render(base::renderer &)      = 0;

    std::uint32_t id() const noexcept
    {
        return p_id;
    }

    bool should_update{true};
    bool should_render{true};

private:
    std::uint32_t p_id;
};

} // namespace sgf

#endif