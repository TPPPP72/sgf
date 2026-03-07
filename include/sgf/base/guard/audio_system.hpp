#ifndef SGF_BASE_GUARD_AUDIO_SYSTEM_HPP
#define SGF_BASE_GUARD_AUDIO_SYSTEM_HPP

namespace sgf::base::guard
{
class audio_system
{
public:
    explicit audio_system();
    ~audio_system();
    audio_system(const audio_system &)                = delete;
    audio_system &operator=(const audio_system &)     = delete;
    audio_system(audio_system &&) noexcept            = default;
    audio_system &operator=(audio_system &&) noexcept = default;
};
}; // namespace sgf::base::guard

#endif