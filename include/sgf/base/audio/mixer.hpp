#ifndef SGF_BASE_MIXER_HPP
#define SGF_BASE_MIXER_HPP

#include "../guard/audio_system.hpp"
#include <memory>

namespace sgf::base
{

class mixer
{
public:
    explicit mixer();
    ~mixer();
    void *get() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    guard::audio_system guard;
};

} // namespace sgf::base

#endif