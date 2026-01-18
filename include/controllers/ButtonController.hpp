#ifndef __ButtonController_hpp__
#define __ButtonController_hpp__

#include <cstdint>
#include <optional>

#include "controllers/Controller.hpp"

namespace Loml {
    enum class ButtonEvent {
        Short,
        Long
    };

    class ButtonController;

    template <>
    struct ControllerSettings<ButtonController> {
        uint8_t  PinNumber           = 0;
        uint64_t LongPressDurationMs = 0;
    };

    template <>
    struct ControllerResult<ButtonController> {
        std::optional<ButtonEvent> Event;
    };

    using ButtonSettings = ControllerSettings<ButtonController>;
    using ButtonResult   = ControllerResult<ButtonController>;

    class ButtonController : public Controller<ButtonController> {
    public:
        friend Controller<ButtonController>;

        ButtonController(const ButtonSettings& settings);
    private:
        void UpdateImpl();
    private:
        ButtonSettings mSettings;
    };
}

#endif