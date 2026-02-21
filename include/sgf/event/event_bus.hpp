#ifndef SGF_EVENT_BUS_HPP
#define SGF_EVENT_BUS_HPP

#include <functional>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace sgf
{

class event_bus
{
public:
    template <typename Event>
    using Handler = std::function<void(Event &)>;

    template <typename Event>
    void subscribe(Handler<Event> handler)
    {
        auto &vec = handlers[typeid(Event)];
        vec.push_back([h = std::move(handler)](void *e) mutable
                      {
                          h(*static_cast<Event *>(e));
                      });
    }

    template <typename Event>
    void emit_now(Event &&e)
    {
        auto it = handlers.find(typeid(Event));
        if (it == handlers.end())
            return;

        for (auto &fn : it->second)
            fn(static_cast<void *>(&e));
    }

    template <typename Event>
    void enqueue(Event &&e)
    {
        using T = std::decay_t<Event>;
        event_queue.push_back([this, event_data = std::forward<Event>(e)]() mutable
                              {
                                  this->emit_now(event_data);
                              });
    }

    void dispatch_all()
    {
        if (event_queue.empty())
            return;

        std::vector<std::function<void()>> processing_vec;
        processing_vec.swap(event_queue);

        for (auto &dispatch_fn : processing_vec)
        {
            dispatch_fn();
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(void *)>>> handlers;
    std::vector<std::function<void()>> event_queue;
};

} // namespace sgf

#endif