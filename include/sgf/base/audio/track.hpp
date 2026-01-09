#ifndef SGF_BASE_TRACK_HPP
#define SGF_BASE_TRACK_HPP

#include "mixer.hpp"

namespace sgf::base
{

class track
{
public:
    track(const mixer &);
    ~track();
    void *get() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
};

} // namespace sgf::base

#endif