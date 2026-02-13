#ifndef Publisher_hpp_
#define Publisher_hpp_

#include "controllers/ControllerSubscriber.hpp"
#include "controllers/ControllerData.hpp"

#include <vector>

namespace Loml
{
    template <typename Derived>
    class Publisher {
    public:
        void Publish(const ControllerResult<Derived>& args);

        void AddSubscriber(ControllerSubscriber<Derived>& sub);
    protected:
        Publisher() = default;
        ~Publisher() = default;
    private:
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
}


#endif