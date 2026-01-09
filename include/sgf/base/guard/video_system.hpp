#ifndef SGF_BASE_GUARD_VIDEO_SYSTEM_HPP
#define SGF_BASE_GUARD_VIDEO_SYSTEM_HPP

namespace sgf::base::guard
{
class video_system
{
public:
    video_system();
    ~video_system();
    video_system(const video_system &)            = delete;
    video_system &operator=(const video_system &) = delete;
    video_system(video_system &&)                 = delete;
    video_system &operator=(video_system &&)      = delete;
};
}; // namespace sgf::base::guard

#endif