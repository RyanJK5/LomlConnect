LomlConnect
==========

LomlConnect allows two LED boards to communicate with each other over a WiFi connection to send heartfelt messages. Users can choose from six patterns to dormantly display on their heart, and can send six different messages to users connected over the same MQTT server.

Usage
--------------
1) Ensure each heart is connected to the WiFi network specified when building (see below).

2) Cycle through idle patterns by pressing the button, or leave the heart on the blank pattern to only listen for incoming messages.

3) Hold the button for one second to open the selection menu and choose a message to send.

4) Cycle through potential messages by pressing the button.

5) Hold the button to send the desired message, or hold the button on the blank screen to cancel.

6) Your message will appear on the other user's heart. The user can then press their button to close the message and can send their own.

Project Layout
--------------
- src/: Application entry points and runtime wiring.
- include/controllers/ and src/controllers/: Controller interfaces and data models.
- include/patterns/ and src/patterns/: LED pattern definitions and implementations.

Build and Upload
----------------
First, update [platformio.ini](platformio.ini) with the relevant details (WiFi login, server URL, etc.).
Use PlatformIO from VS Code or the CLI:


```
# Build firmware
pio run

# Upload to the device
pio run -t upload

# Monitor console logging
pio device monitor
``` 

**IMPORTANT:** The `NeoPixelBus` library was modified to make `RgbColor`'s two implicit constructors `constexpr`. Please make these changes to compile the code properly.

License
-------
