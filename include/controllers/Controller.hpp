#ifndef Controller_hpp_
#define Controller_hpp_

#include "controllers/ControllerData.hpp"
#include "controllers/Publisher.hpp"

namespace Loml {
    struct TaskSettings {
        const char* Name       = "";
        uint32_t    StackDepth = 0;
        BaseType_t  CoreID     = 0;
    };

    template <typename Derived>
    class Controller : public Publisher<Derived> {
    public:
        void CreateTask(const TaskSettings& taskSettings);
    protected:
        ~Controller() = default;

        friend Derived;
    private:
        Controller(const ControllerSettings<Derived>& controllerSettings);
    };

    template <typename Derived>
    Controller<Derived>::Controller(const ControllerSettings<Derived>&) { }

    template <typename Derived>
    void Controller<Derived>::CreateTask(const TaskSettings& taskSettings) {
        constexpr static auto updateTask = [](void* self){ 
            while (true) {
                static_cast<Derived*>(self)->UpdateImpl(); 
            }
        };
        
        xTaskCreatePinnedToCore(
            updateTask, 
            taskSettings.Name, 
            taskSettings.StackDepth, 
            static_cast<Derived*>(this),
            2,
            nullptr, 
            taskSettings.CoreID
        );
    }
}
#endif