#include <Arduino.h>
#include <WiFi.h>
#include <WiFiEnterprise.h>

#include "controllers/WiFiController.hpp"

namespace Loml {
	WiFiController::WiFiController(const WiFiSettings& settings) 
		: Controller{settings}
		, mServerSettings{settings.Server}
	{
		Serial.println("Connecting...");
		
		if (!settings.Local.IsEnterprise()) {
		    WiFi.begin(settings.Local.NetworkName, settings.Local.Password);
		    delay(500);
			while (WiFi.status() != WL_CONNECTED) {
		        delay(500);
		        Serial.print(".");
		    }
			Serial.println();
		    Serial.println("Connected successful!");
		}
		else {
		    if (WiFiEnterprise.begin(settings.Local.NetworkName, settings.Local.Username, settings.Local.Password)) {
			    Serial.println("Connection successful!");
			    Serial.print("IP Address: ");
			    Serial.println(WiFiEnterprise.localIP());
			    Serial.print("Status: ");
			    Serial.println(WiFiEnterprise.status());
		    }
		    else {
			    Serial.println("Connection failed!");
			    Serial.println("Please check your credentials and network settings.");
		    }
		}
	
		mPubSub.setClient(mWifiClient);
		mWifiClient.setInsecure();
	
		mPubSub.setServer(settings.Server.NetworkName, settings.Server.Port);
		mPubSub.setCallback([&](char* topic, byte*, unsigned int length){
			Serial.println("Message received");
			Publish({});
		});
	}
	
	void WiFiController::Reconnect() {
		while (!mPubSub.connected()) {
			Serial.println("Connecting to MQTT Broker...");
			if (mPubSub.connect(mServerSettings.SessionID, mServerSettings.Username, mServerSettings.Password)) {
				Serial.println("Connected to MQTT Broker.");
				mPubSub.subscribe(mServerSettings.Subscription);
			} 
			else {
				Serial.print("Error ");
				Serial.print(mPubSub.state());
				vTaskDelay(pdMS_TO_TICKS(5000));
			}
		}
	}
	
	void WiFiController::UpdateImpl() {
		vTaskDelay(pdMS_TO_TICKS(100));
		
		if (!mPubSub.connected()) {
			Reconnect();
		}
		mPubSub.loop();
	}
	
	void WiFiController::OnMessage(const ButtonResult& args) {
		if (args.Event == ButtonEvent::Short) {
			return;
		}

		mPubSub.publish(mServerSettings.Username, "");
		Serial.println("Published message");
	}
}