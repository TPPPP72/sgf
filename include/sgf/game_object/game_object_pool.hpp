#ifndef SGF_GAME_OBJECT_POOL_HPP
#define SGF_GAME_OBJECT_POOL_HPP

#include "../base/renderer.hpp"
#include <chrono>
#include <memory>
#include <vector>

namespace sgf
{

class game_object;

struct game_object_handle
{
    std::size_t index;
    std::uint32_t version;
};

class game_object_pool
{
public:
    game_object_pool()                                    = default;
    ~game_object_pool()                                   = default;
    game_object_pool(const game_object_pool &)            = delete;
    game_object_pool &operator=(const game_object_pool &) = delete;
    game_object *get(game_object_handle);
    game_object_handle create(std::unique_ptr<game_object> obj);
    bool remove(game_object_handle);
    void update(std::chrono::nanoseconds dt);
    void render(base::renderer &);

private:
    struct entry
    {
        std::unique_ptr<game_object> obj;
        std::uint32_t version;
    };
    std::vector<entry> p_objects;
};

}; // namespace sgf

#endif