#include <SDL3_ttf/SDL_ttf.h>
#include <sgf/base/font.hpp>

using namespace sgf::base;

struct font::impl
{
    TTF_Font *font = nullptr;
};

font::font(const std::filesystem::path &p, std::uint32_t size) : p_impl(std::make_unique<impl>())
{
    p_impl->font = TTF_OpenFont(p.string().c_str(), size);

    if (p_impl->font == nullptr)
        throw std::runtime_error(SDL_GetError());
}

font::~font()
{
    TTF_CloseFont(p_impl->font);
}

void *font::get() const noexcept
{
    return p_impl->font;
}