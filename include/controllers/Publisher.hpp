#ifndef __Publisher_hpp__
#define __Publisher_hpp__

#include "controllers/ControllerSubscriber.hpp"
#include "controllers/ControllerData.hpp"

#include <vector>

namespace Loml
{
    template <typename T>
    class Publisher {
    public:
        Publisher() = default;
        virtual ~Publisher() = default;

        void Publish(const ControllerResult<T>& args);

        void AddSubscriber(ControllerSubscriber<T>& sub);
    private:
        std::vector<ControllerSubscriber<T>*> mSubscribers;
    };

    template <typename T>
    void Publisher<T>::Publish(const ControllerResult<T>& args) {
        for (auto* sub : mSubscribers) {
            sub->OnMessage(args);
        }
    }

    template <typename T>
    void Publisher<T>::AddSubscriber(ControllerSubscriber<T>& sub) {
        mSubscribers.push_back(&sub);
    }
}


#endif