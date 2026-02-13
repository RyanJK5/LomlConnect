#ifndef LEDResult_hpp_
#define LEDResult_hpp_

#include "ControllerData.hpp"

namespace Loml {
    class LEDController;
    
    template <>
    struct ControllerResult<LEDController> {
        size_t PatternIndex = 0;
    };
    
    using LEDResult = ControllerResult<LEDController>;
}

#endif