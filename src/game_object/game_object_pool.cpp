#include <sgf/game_object/game_object.hpp>
#include <sgf/game_object/game_object_pool.hpp>

sgf::game_object *sgf::game_object_pool::get(sgf::game_object_handle handle)
{
    if (handle.index >= p_objects.size())
        return nullptr;

    auto &entry = p_objects[handle.index];

    if (!entry.obj || entry.version != handle.version)
        return nullptr;

    return entry.obj.get();
}

sgf::game_object_handle sgf::game_object_pool::create(std::unique_ptr<sgf::game_object> obj)
{
    for (std::size_t i = 0; i < p_objects.size(); ++i)
    {
        if (p_objects[i].obj == nullptr)
        {
            ++p_objects[i].version;
            p_objects[i].obj = std::move(obj);
            return {i, p_objects[i].version};
        }
    }

    p_objects.push_back({std::move(obj), 1});
    return {p_objects.size() - 1, 1};
}

bool sgf::game_object_pool::remove(sgf::game_object_handle handle)
{
    if (handle.index >= p_objects.size())
        return false;

    auto &entry = p_objects[handle.index];

    if (entry.obj != nullptr && entry.version == handle.version)
    {
        entry.obj.reset();
        return true;
    }

    return false;
}

void sgf::game_object_pool::update(std::chrono::nanoseconds dt)
{
    for (std::size_t i = 0; i < p_objects.size(); ++i)
    {
        auto &entry = p_objects[i];

        if (entry.obj == nullptr)
            continue;

        if (entry.obj->is_active())
            entry.obj->on_update(dt);

        if (entry.obj->is_pending_destruction())
            entry.obj.reset();
    }
}

void sgf::game_object_pool::render(sgf::base::renderer &r)
{
    for (const auto &entry : p_objects)
    {
        if (entry.obj != nullptr && entry.obj->is_active())
            entry.obj->on_render(r);
    }
}