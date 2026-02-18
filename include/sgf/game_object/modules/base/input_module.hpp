#ifndef SGF_GAME_OBJECT_MODULES_BASE_INPUT_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_BASE_INPUT_MODULE_HPP

#include <chrono>

namespace sgf
{

class game_object;

namespace module
{

class base_input_module
{
public:
    explicit base_input_module(game_object &owner) : m_owner(owner) {}
    virtual ~base_input_module() = default;

    base_input_module(const base_input_module &)            = delete;
    base_input_module &operator=(const base_input_module &) = delete;

    virtual void update(std::chrono::nanoseconds dt) {}

protected:
    game_object &owner() const noexcept { return m_owner; }

private:
    game_object &m_owner;
};

} // namespace module

} // namespace sgf

#endif