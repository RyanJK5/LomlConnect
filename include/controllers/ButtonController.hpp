#ifndef ButtonController_hpp_
#define ButtonController_hpp_

#include <cstdint>
#include <optional>

#include "controllers/Controller.hpp"

namespace Loml {
    enum struct PatternMode {
        Default,
        ConfirmingSent,
        ConfirmingReceived,
        Sending,
        Receiving
    };

    enum struct ButtonEvent {
        Cycle,
        SelectMessage,
        SendMessage,
    };

    class ButtonController;

    template <>
    struct ControllerSettings<ButtonController> {
        uint8_t  PinNumber           = 0;
        uint64_t LongPressDurationMs = 0;
    };

    template <>
    struct ControllerResult<ButtonController> {
        ButtonEvent Event;
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
        PatternMode mMode = PatternMode::Default;
        ButtonSettings mSettings;
    };
}

#endif