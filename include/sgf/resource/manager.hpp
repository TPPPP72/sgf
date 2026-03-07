#ifndef SGF_RESOURCE_MANAGER_HPP
#define SGF_RESOURCE_MANAGER_HPP

#include <memory>
#include <sgf/base/audio/audio.hpp>
#include <sgf/base/font.hpp>
#include <sgf/base/surface.hpp>
#include <sgf/base/texture.hpp>
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
        std::unordered_map<std::uint32_t, T> data;
    };

public:
    void load_surface(const std::filesystem::path &p, std::uint32_t key)
    {
        add(key, base::surface{p});
    }
    void load_texture(const base::surface &surf, const base::renderer &rend, std::uint32_t key)
    {
        add(key, base::texture{rend, surf});
    }
    void load_texture(const std::filesystem::path &p, const base::renderer &rend, std::uint32_t key)
    {
        add(key, base::texture{rend, p});
    }
    void load_font(const std::filesystem::path &p, std::uint32_t size, std::uint32_t key)
    {
        add(key, base::font{p, size});
    }
    void load_audio(const std::filesystem::path &p, std::uint32_t key)
    {
        add(key, base::audio{p});
    }
    template <typename T>
    void add(std::uint32_t key, T &&res)
    {
        auto *pool      = get_or_create_pool<T>();
        pool->data.try_emplace(key, std::forward<T>(res));
    }

    template <typename T>
    T *get(std::uint32_t key)
    {
        auto *pool = get_or_create_pool<T>();
        auto it    = pool->data.find(key);
        return (it != pool->data.end()) ? &it->second : nullptr;
    }

private:
    static std::uint32_t get_next_type_id()
    {
        static std::uint32_t count = -1;
        ++count;
        return count;
    }

    template <typename T>
    static std::uint32_t get_type_id()
    {
        static const std::uint32_t id = get_next_type_id();
        return id;
    }

    std::unordered_map<std::uint32_t, std::unique_ptr<pool_base>> m_pools;

    template <typename T>
    resource_pool<T> *get_or_create_pool()
    {
        std::uint32_t tid = get_type_id<T>();
        if (m_pools.find(tid) == m_pools.end())
        {
            m_pools[tid] = std::make_unique<resource_pool<T>>();
        }
        return static_cast<resource_pool<T> *>(m_pools[tid].get());
    }
};

} // namespace sgf::resource

#endif