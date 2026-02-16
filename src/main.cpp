#include <Arduino.h>
#include <optional>

#include "Application.hpp"
#include "Config.hpp"

// Put in static storage so it can survive past setup()
// Stored in an optional to avoid default construction before Serial.begin()
static std::optional<Loml::Application> app; 

void setup() {
	constexpr static auto baud = 115200UL;
	Serial.begin(baud);

	delay(1000);

	app.emplace( // Call constructor with default settings
		Loml::Config::DefaultLEDSettings,
		Loml::Config::DefaultButtonSettings,
		Loml::WiFiSettings{Loml::Config::DefaultLocalSettings, Loml::Config::DefaultServerSettings}
	);
	app->Begin();
}

void loop() { }