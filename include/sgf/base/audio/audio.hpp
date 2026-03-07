#ifndef SGF_BASE_AUDIO_HPP
#define SGF_BASE_AUDIO_HPP

#include "../guard/audio_system.hpp"
#include <filesystem>
#include <memory>

namespace sgf::base
{

class audio
{
public:
    explicit audio(const std::filesystem::path &);
    ~audio();
    audio(const audio &)                = delete;
    audio operator=(const audio &)      = delete;
    audio(audio &&) noexcept;
    audio &operator=(audio &&) noexcept;
    void *get() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    guard::audio_system guard;
};

} // namespace sgf::base

#endif