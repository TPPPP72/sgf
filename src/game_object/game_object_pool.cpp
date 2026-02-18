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
    std::size_t target_idx;
    std::uint32_t target_ver;
    bool reused = false;

    for (std::size_t i = 0; i < p_objects.size(); ++i)
    {
        if (p_objects[i].obj == nullptr)
        {
            p_objects[i].obj = std::move(obj);
            target_ver       = ++p_objects[i].version;
            target_idx       = i;
            reused           = true;
            break;
        }
    }

    if (!reused)
    {
        p_objects.push_back({std::move(obj), 1});
        target_idx = p_objects.size() - 1;
        target_ver = 1;
    }

    p_objects[target_idx].obj->on_init(p_ctx);

    return {target_idx, target_ver};
}

bool sgf::game_object_pool::remove(sgf::game_object_handle handle)
{
    if (handle.index >= p_objects.size())
        return false;

    auto &entry = p_objects[handle.index];

    if (entry.obj != nullptr && entry.version == handle.version)
    {
        entry.obj.reset();
        ++entry.version;
        return true;
    }

    return false;
}

void sgf::game_object_pool::update(std::chrono::nanoseconds dt)
{
    for (std::size_t i = 0; i < p_objects.size(); ++i)
    {
        if (p_objects[i].obj && p_objects[i].obj->is_active())
        {
            auto &input_modules = p_objects[i].obj->p_input_modules;
            for (auto &&module : input_modules)
                module->update(dt);

            p_objects[i].obj->on_update(dt);
        }
    }

    for (std::size_t i = 0; i < p_objects.size(); ++i)
    {
        if (p_objects[i].obj && p_objects[i].obj->is_pending_destruction())
        {
            p_objects[i].obj.reset();
            ++p_objects[i].version;
        }
    }
}

void sgf::game_object_pool::render()
{
    for (const auto &entry : p_objects)
    {
        if (entry.obj && entry.obj->is_active() && entry.obj->p_render_module)
            entry.obj->on_render();
    }
}