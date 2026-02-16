#ifndef Publisher_hpp_
#define Publisher_hpp_

#include "controllers/ControllerSubscriber.hpp"
#include "controllers/ControllerData.hpp"

#include <vector>

namespace Loml
{
    template <typename Derived> // CRTP
    class Publisher {
    public:
        void Publish(const ControllerResult<Derived>& args);

        void AddSubscriber(ControllerSubscriber<Derived>& sub);

        void RemoveSubscriber(ControllerSubscriber<Derived>& sub);
    protected:
        Publisher() = default;
        ~Publisher() = default;
    private:
        // Raw pointers are a not-great solution to storing a reference to subscribers.
        // Ideally a weak_ptr-like object could be used to check if the subscriber is
        // alive, but that adds overhead because it requires a shared_ptr. Instead,
        // clients are expected to remove subscribers as necessary.
        std::vector<ControllerSubscriber<Derived>*> mSubscribers;
    };

    template <typename Derived>
    void Publisher<Derived>::Publish(const ControllerResult<Derived>& args) {
        for (auto* sub : mSubscribers) {
            sub->OnMessage(args);
        }
    }

    template <typename Derived>
    void Publisher<Derived>::AddSubscriber(ControllerSubscriber<Derived>& sub) {
        mSubscribers.push_back(&sub);
    }

    template <typename Derived>
    void Publisher<Derived>::RemoveSubscriber(ControllerSubscriber<Derived>& sub) {
        mSubscribers.erase(std::find(mSubscribers.begin(), mSubscribers.end(), sub));
    }
}


#endif