#include <unity.h>

#include "TestModules.hpp"

void setup() {
    UNITY_BEGIN();

    Loml::ControllerTest::Run();

    UNITY_END();
}

void loop() { }