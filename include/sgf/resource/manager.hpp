#ifndef SGF_RESOURCE_MANAGER_HPP
#define SGF_RESOURCE_MANAGER_HPP

#include <memory>
#include <queue>
#include <sgf/base/audio/audio.hpp>
#include <sgf/base/font.hpp>
#include <sgf/base/surface.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/literals/hash.hpp>
#include <sgf/resource/data.hpp>
#include <unordered_map>

namespace sgf::resource
{

class manager
{
    struct pool_base
    {
        virtual ~pool_base() = default;
    };

    template <typename T>
    struct resource_pool : public pool_base
    {
        std::unordered_map<sgf::type::uint32, T> data;
    };

    struct task
    {
        sgf::type::uint32 key;
        base::surface surf;
    };

public:
    void load_surface(const std::filesystem::path &p, sgf::type::uint32 key)
    {
        upload_list.emplace(task{key, base::surface{p}});
    }
    void load_texture(const base::surface &surf, const base::renderer &rend, sgf::type::uint32 key)
    {
        add(key, base::texture{rend, surf});
    }
    void load_texture(const std::filesystem::path &p, const base::renderer &rend, sgf::type::uint32 key)
    {
        add(key, base::texture{rend, p});
    }
    void load_font(const std::filesystem::path &p, sgf::type::uint32 size, sgf::type::uint32 key)
    {
        add(key, base::font{p, size});
    }
    void load_audio(const std::filesystem::path &p, sgf::type::uint32 key)
    {
        add(key, base::audio{p});
    }
    void load_asset(const asset &as)
    {
        using namespace sgf::literals;
        if (as.type == "texture"_hash)
        {
            load_surface(as.path, as.key);
            return;
        }
        if (as.type == "audio"_hash)
        {
            load_audio(as.path, as.key);
            return;
        }
        if (as.type == "font"_hash)
        {
            load_font(as.path, 24, as.key);
            return;
        }
    }
    void upload_surface(const base::renderer &rend)
    {
        auto key = upload_list.front().key;
        load_texture(upload_list.front().surf, rend, key);
        upload_list.pop();
    }
    void upload_all_surface(const base::renderer &rend)
    {
        while (!upload_list.empty())
        {
            upload_surface(rend);
        }
    }

    template <typename T>
    void add(sgf::type::uint32 key, T &&res)
    {
        auto *pool = get_or_create_pool<T>();
        pool->data.try_emplace(key, std::forward<T>(res));
    }

    template <typename T>
    T *get(sgf::type::uint32 key)
    {
        auto *pool = get_or_create_pool<T>();
        auto it    = pool->data.find(key);
        return (it != pool->data.end()) ? &it->second : nullptr;
    }

private:
    static sgf::type::uint32 get_next_type_id()
    {
        static sgf::type::uint32 count = 0;
        return count++;
    }

    template <typename T>
    static sgf::type::uint32 get_type_id()
    {
        static const sgf::type::uint32 id = get_next_type_id();
        return id;
    }

    std::unordered_map<sgf::type::uint32, std::unique_ptr<pool_base>> m_pools;

    template <typename T>
    resource_pool<T> *get_or_create_pool()
    {
        sgf::type::uint32 tid = get_type_id<T>();
        if (m_pools.find(tid) == m_pools.end())
        {
            m_pools[tid] = std::make_unique<resource_pool<T>>();
        }
        return static_cast<resource_pool<T> *>(m_pools[tid].get());
    }

    std::queue<task> upload_list;
};

} // namespace sgf::resource

#endif