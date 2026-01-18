#ifndef __ControllerSubscriber_hpp__
#define __ControllerSubscriber_hpp__

#include "controllers/ControllerData.hpp"

namespace Loml {
    template <typename Controller>
    class ControllerSubscriber {
    public:
        virtual void OnMessage(const ControllerResult<Controller>& args) = 0;
    };
}

#endif