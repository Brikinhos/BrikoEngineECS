#pragma once
#include <any>
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <cstdint>
#include <algorithm>

namespace ecs {

class EventBus {
public:
    using HandlerId = std::uint64_t;
    using HandlerFn = std::function<void(const std::any&)>;

    // Suscripción
    template<typename Event, typename Fn>
    //requires std::invocable<Fn, const Event&>
    HandlerId subscribe(Fn&& fn) {
        //Guardamos el identificador del tipo de Event
        std::type_index ti(typeid(Event));
        //
        auto wrapper = [f = std::forward<Fn>(fn)](const std::any& a) {
            f(std::any_cast<const Event&>(a));
        };

        HandlerId id = nextHandlerId_++;
        subscribers_[ti].emplace_back(id, std::move(wrapper));
        return id;
    }

    // Desuscripción
    template<typename Event>
    void unsubscribe(HandlerId id) {
        std::type_index ti(typeid(Event));
        auto& vec = subscribers_[ti];
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [id](auto& p){ return p.first == id; }), vec.end());
    }

    // Emit encolado
    template<typename Event>
    void emit(const Event& ev) {
        queue_.emplace_back(std::type_index(typeid(Event)), std::any(ev));
    }

    template<typename Event>
    void emit(Event&& ev) {
        queue_.emplace_back(std::type_index(typeid(std::decay_t<Event>)),
                            std::any(std::forward<Event>(ev)));
    }

    // Procesa todos los eventos encolados
    void processQueue() {
        auto temp = std::move(queue_);
        queue_.clear();
        for (auto& [ti, ev] : temp) {
            auto it = subscribers_.find(ti);
            if (it == subscribers_.end()) continue;
            for (auto& [id, handler] : it->second) {
                handler(ev);
            }
        }
    }

private:
    HandlerId nextHandlerId_ = 0;
    std::unordered_map<std::type_index, std::vector<std::pair<HandlerId, HandlerFn>>> subscribers_;
    std::vector<std::pair<std::type_index, std::any>> queue_;
};

}