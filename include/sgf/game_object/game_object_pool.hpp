#ifndef SGF_GAME_OBJECT_POOL_HPP
#define SGF_GAME_OBJECT_POOL_HPP

#include <memory>
#include <vector>

namespace sgf
{

class game_object;

class scene_context;
class frame_context;
class input_event;

struct game_object_handle
{
    std::size_t index;
    std::uint32_t version;
};

class game_object_pool
{
public:
    explicit game_object_pool(scene_context &ctx) : p_ctx(ctx) {}
    ~game_object_pool()                                   = default;
    game_object_pool(const game_object_pool &)            = delete;
    game_object_pool &operator=(const game_object_pool &) = delete;
    game_object *get(game_object_handle);
    game_object_handle create(std::unique_ptr<game_object>);
    bool remove(game_object_handle);
    void input(const input_event &);
    void update(const frame_context &);
    void render();

private:
    struct entry
    {
        std::unique_ptr<game_object> obj;
        std::uint32_t version;
    };
    std::vector<entry> p_objects;
    scene_context &p_ctx;
};

}; // namespace sgf

#endif