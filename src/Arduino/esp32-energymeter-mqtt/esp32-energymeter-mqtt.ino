/*
 * Project: esp32-energymeter-mqtt
 * 
 * Description:
 * This project is designed to monitor and report energy consumption using an ESP32 microcontroller and the ATM90E32 energy metering IC. 
 * The collected energy data is sent to a Home Assistant server via MQTT. The ESP32 connects to a WiFi network and communicates with 
 * an MQTT broker to publish energy metrics, making it accessible for home automation and monitoring purposes.
 * 
 * Key Features:
 * - Energy Monitoring: Utilizes the ATM90E32 IC to measure voltage, current, and power metrics.
 * - WiFi Connectivity: Connects to a specified WiFi network for seamless integration with IoT systems.
 * - MQTT Communication: Sends energy data to a Home Assistant or other MQTT-compatible platforms for real-time monitoring.
 * - Debugging: Optional serial debugging to assist in development and troubleshooting.
 * 
 * Libraries Used:
 * - ATM90E32 [https://github.com/CircuitSetup/ATM90E32]:  Handles communication with the energy metering IC.
 * - MQTTPubSubClient [https://github.com/hideakitai/MQTTPubSubClient]: Manages MQTT communication for sending data to Home Assistant.
 * 
 * Getting Started:
 * To get started, open the config.ino file and set the following parameters:
 * - WiFi Credentials:
 *   - WIFISSID: Your WiFi network SSID.
 *   - WIFIPASSWORD: Your WiFi network password.
 * - MQTT Broker Configuration:
 *   - HOMEASSISTANT_IP: The IP address of your Home Assistant or MQTT broker.
 *   - DEVICE_NAME: The name of your device.
 *   - USER_ID: The username for your MQTT broker.
 *   - PASSWORD: The password for your MQTT broker.
 * - Debugging:
 *   - DEBUG: Set to true if you want to use the Serial Monitor for debugging.
 * 
 * Author: Saad Imtiaz
 * Date: 25th June, 2024
 */

#include <WiFi.h>
#include <SPI.h>
#include <ATM90E32.h>
#include <MQTTPubSubClient.h>
#include <config.ino> // Include configuration file for WiFi and MQTT details

// WiFi Credentials
const char* ssid = WIFISSID;       // Your WiFi SSID
const char* pass = WIFIPASSWORD;   // Your WiFi Password

WiFiClient client;
MQTTPubSubClient mqtt;

ATM90E32 energymeter{};

void setup() {
  /* Initialize the serial port for debugging if DEBUG is set to true */
  #if DEBUG == true
  Serial.begin(115200);
  Serial.println("Start ATM90E32"); // Debugging message to indicate the start of ATM90E32 initialization
  #endif

  /* Initialize the ATM90E32 energy meter with the specified parameters */
  energymeter.begin(CS_PIN, LINEFREQ, PGA_GAIN, VOLTAGE_GAIN, GAIN_CT_A, GAIN_CT_B, GAIN_CT_C);
  
  /* Set up the GREEN_LED pin as an output and turn it off initially */
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);

  /* Begin the WiFi connection using the provided SSID and password */
  WiFi.begin(ssid, pass);
  
  /* Initialize the MQTT client */
  mqtt.begin(client);

  /* Connect to WiFi, MQTT broker, and Home Assistant */
  connect();

  /* Set up a subscription to handle incoming MQTT messages */
  mqtt.subscribe([](const String& topic, const String& payload, const size_t size) {
    #if DEBUG == true
    Serial.println("mqtt received: " + topic + " - " + payload); // Debugging message to show received MQTT messages
    #endif
  });

  /* Subscribe to the /hello topic and set up a callback for incoming messages */
  mqtt.subscribe("/hello", [](const String& payload, const size_t size) {
    #if DEBUG == true
    Serial.print("/hello ");
    Serial.println(payload); // Debugging message to show the payload of the /hello topic
    #endif
  });
}

void loop() {
  /* Keep the MQTT client updated */
  mqtt.update();

  /* Reconnect to the MQTT broker if the connection is lost */
  if (!mqtt.isConnected()) {
    connect();
  }

  /* Check and send energy data to Home Assistant every 3 seconds */
  static uint32_t prev_ms = millis();
  if (millis() > prev_ms + 3000) {
    prev_ms = millis();
    getEnergyData(); // Retrieve energy data and send via MQTT
  }
}
