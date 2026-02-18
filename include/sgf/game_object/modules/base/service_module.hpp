#ifndef SGF_GAME_OBJECT_MODULES_BASE_SERVICE_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_BASE_SERVICE_MODULE_HPP

namespace sgf
{

class game_object;

class scene_context;

namespace module
{

class base_service_module
{
public:
    explicit base_service_module(game_object &owner, scene_context &context) : m_owner(owner), m_context(context) {}
    virtual ~base_service_module() = default;

    base_service_module(const base_service_module &)            = delete;
    base_service_module &operator=(const base_service_module &) = delete;

protected:
    game_object &owner() const noexcept { return m_owner; }
    scene_context &context() const noexcept { return m_context; }

private:
    game_object &m_owner;
    scene_context &m_context;
};

} // namespace module

} // namespace sgf

#endif