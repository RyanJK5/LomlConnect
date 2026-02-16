#ifndef ButtonController_hpp_
#define ButtonController_hpp_

#include <cstdint>
#include <optional>

#include "controllers/Controller.hpp"

namespace Loml {
    // Represents the various states of the program
    enum struct PatternMode {
        Default, // Showing one of the typical patterns
        ConfirmingSent, // Displaying confirmation for sending a pattern
        ConfirmingReceived, // Displaying confirmation for receiving a pattern
        Sending, // Selecting a pattern to send
        Receiving // Displaying a received pattern
    };

    enum struct ButtonEvent {
        Cycle, // Proceed to next pattern
        SelectMessage, // Open prompt to select a message
        SendMessage // Confirm sending the selected message
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
        friend Controller<ButtonController>; // Exposes access to UpdateImpl

        ButtonController(const ButtonSettings& settings);
    private:
        void UpdateImpl();
    private:
        PatternMode mMode = PatternMode::Default;
        ButtonSettings mSettings;
    };
}

#endif