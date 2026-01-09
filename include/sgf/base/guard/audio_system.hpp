#ifndef SGF_BASE_GUARD_AUDIO_SYSTEM_HPP
#define SGF_BASE_GUARD_AUDIO_SYSTEM_HPP

namespace sgf::base::guard
{
class audio_system
{
public:
    audio_system();
    ~audio_system();
    audio_system(const audio_system &)            = delete;
    audio_system &operator=(const audio_system &) = delete;
    audio_system(audio_system &&)                 = delete;
    audio_system &operator=(audio_system &&)      = delete;
};
}; // namespace sgf::base::guard

#endif