#include <Arduino.h>
#include <optional>

#include "Application.hpp"
#include "Config.hpp"

std::optional<Loml::Application> app;

void setup() {
	Serial.begin(115200);
	delay(1000);

	app.emplace(
		Loml::Config::DefaultLEDSettings,
		Loml::Config::DefaultButtonSettings,
		Loml::WiFiSettings{Loml::Config::DefaultLocalSettings, Loml::Config::DefaultServerSettings}
	);
	app->Begin();
}

void loop() { }