#ifndef ControllerSubscriber_hpp_
#define ControllerSubscriber_hpp_

#include "controllers/ControllerData.hpp"

namespace Loml {
    template <typename Controller>
    class ControllerSubscriber {
    public:
        virtual void OnMessage(const ControllerResult<Controller>& args) = 0;
    };
}

#endif