
void getEnergyData() {

// Retrieve system status from the ATM90E32
  unsigned short sys0 = energymeter.GetSysStatus0();   //EMMState0
  unsigned short sys1 = energymeter.GetSysStatus1();   //EMMState1
  unsigned short en0 = energymeter.GetMeterStatus0();  //EMMIntState0
  unsigned short en1 = energymeter.GetMeterStatus1();  //EMMIntState1

  // Print system and meter status for debugging
  Serial.println("Sys Status: S0:0x" + String(sys0, HEX) + " S1:0x" + String(sys1, HEX));
  Serial.println("Meter Status: E0:0x" + String(en0, HEX) + " E1:0x" + String(en1, HEX));
  delay(10);

// Check if the MCU is not receiving data from the energy meter
  if (sys0 == 65535 || sys0 == 0) Serial.println("Error: Not receiving data from energy meter - check your connections");

// Retrieve all parameters from the ATM90E32
float lineVoltageA = energymeter.GetLineVoltageA();
float lineVoltageB = energymeter.GetLineVoltageB();
float lineVoltageC = energymeter.GetLineVoltageC();

float lineCurrentA = energymeter.GetLineCurrentA();
float lineCurrentB = energymeter.GetLineCurrentB();
float lineCurrentC = energymeter.GetLineCurrentC();
float lineCurrentN = energymeter.GetLineCurrentN();
float totalCurrent = lineCurrentA + lineCurrentB + lineCurrentC;

float activePowerA = energymeter.GetActivePowerA();
float activePowerB = energymeter.GetActivePowerB();
float activePowerC = energymeter.GetActivePowerC();
float totalActivePower = energymeter.GetTotalActivePower();

float activeFundPower = energymeter.GetTotalActiveFundPower();
float activeHarPower = energymeter.GetTotalActiveHarPower();

float reactivePowerA = energymeter.GetReactivePowerA();
float reactivePowerB = energymeter.GetReactivePowerB();
float reactivePowerC = energymeter.GetReactivePowerC();
float totalReactivePower = energymeter.GetTotalReactivePower();

float apparentPowerA = energymeter.GetApparentPowerA();
float apparentPowerB = energymeter.GetApparentPowerB();
float apparentPowerC = energymeter.GetApparentPowerC();
float totalApparentPower = energymeter.GetTotalApparentPower();

float frequency = energymeter.GetFrequency();

float powerFactorA = energymeter.GetPowerFactorA();
float powerFactorB = energymeter.GetPowerFactorB();
float powerFactorC = energymeter.GetPowerFactorC();
float totalPowerFactor = energymeter.GetTotalPowerFactor();

float phaseAngleA = energymeter.GetPhaseA();
float phaseAngleB = energymeter.GetPhaseB();
float phaseAngleC = energymeter.GetPhaseC();

float temperature = energymeter.GetTemperature();

// Energy Consumption
float importEnergy = energymeter.GetImportEnergy();
float importReactiveEnergy = energymeter.GetImportReactiveEnergy();
float importApparentEnergy = energymeter.GetImportApparentEnergy();
float exportEnergy = energymeter.GetExportEnergy();
float exportReactiveEnergy = energymeter.GetExportReactiveEnergy();
  
  // Send all the collected energy data via MQTT to Home Assistant
  mqtt.publish("esp32energymeter/lineCurrentA", String(lineCurrentA).c_str());
  mqtt.publish("esp32energymeter/lineCurrentB", String(lineCurrentB).c_str());
  mqtt.publish("esp32energymeter/lineCurrentC", String(lineCurrentC).c_str());
  mqtt.publish("esp32energymeter/totalCurrent", String(totalCurrent).c_str());

  mqtt.publish("esp32energymeter/lineVoltageA", String(lineVoltageA).c_str());
  mqtt.publish("esp32energymeter/lineVoltageB", String(lineVoltageB).c_str());
  mqtt.publish("esp32energymeter/lineVoltageC", String(lineVoltageA).c_str());
  
  mqtt.publish("esp32energymeter/totalActivePower", String(totalActivePower).c_str());
  mqtt.publish("esp32energymeter/totalReactivePower", String(totalReactivePower).c_str());
  mqtt.publish("esp32energymeter/totalPowerFactor", String(totalPowerFactor).c_str());

  mqtt.publish("esp32energymeter/temperature", String(temperature).c_str());

  mqtt.publish("esp32energymeter/frequency", String(frequency).c_str());

  mqtt.publish("esp32energymeter/powerFactor", String(importEnergy).c_str());

  mqtt.publish("esp32energymeter/importEnergy", String(importEnergy).c_str());
  mqtt.publish("esp32energymeter/exportEnergy", String(exportEnergy).c_str());

 // Debugging: Print all energy data to the Serial Monitor if DEBUG is enabled
#if DEBUG == true
  Serial.println("Voltage A: " + String(lineVoltageA) + "V");
  Serial.println("Voltage B: " + String(lineVoltageB) + "V");
  Serial.println("Voltage C: " + String(lineVoltageC) + "V");

  Serial.println("Current A: " + String(lineCurrentA) + "A");
  Serial.println("Current B: " + String(lineCurrentB) + "A");
  Serial.println("Current C: " + String(lineCurrentC) + "A");

  Serial.println("Active Power: " + String(totalActivePower) + "W");
  Serial.println("Total Power Factor: " + String(totalPowerFactor));

  Serial.println("Fundimental Power: " + String(energymeter.GetTotalActiveFundPower()) + "W");
  Serial.println("Harmonic Power: " + String(energymeter.GetTotalActiveHarPower()) + "W");
  Serial.println("Reactive Power: " + String(energymeter.GetTotalReactivePower()) + "var");
  Serial.println("Apparent Power: " + String(energymeter.GetTotalApparentPower()) + "VA");
  Serial.println("Phase Angle A: " + String(energymeter.GetPhaseA()));

  Serial.println("Chip Temp: " + String(temperature) + "C");
  Serial.println("Frequency: " + String(frequency) + "Hz");
#endif


}


void connect() {
connect_to_wifi:
#if DEBUG == true
  Serial.print("Connecting to WiFi...");
#endif
  // Attempt to connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
#if DEBUG == true
  Serial.println(" CONNECTED!");
#endif
connect_to_host:
#if DEBUG == true
  Serial.print("Connecting to Host...");
#endif
// Disconnect and attempt to connect to the MQTT broker
  client.stop();
  while (!client.connect(HOMEASSISTANT_IP, 1883)) {
    delay(1000);
    if (WiFi.status() != WL_CONNECTED) {
#if DEBUG == true
      Serial.println("WiFi Disconnected");
#endif
      goto connect_to_wifi;
    }
  }
#if DEBUG == true
  Serial.println("  CONNECTED!");
  Serial.print("Connecting to MQTT Broker...");
#endif
 // Disconnect MQTT and attempt to reconnect
  mqtt.disconnect();
  while (!mqtt.connect(DEVICE_NAME, USER_ID, PASSWORD)) {
    delay(1000);
    if (WiFi.status() != WL_CONNECTED) {
#if DEBUG == true
      Serial.println("WiFi Disconnected");
#endif
 digitalWrite(GREEN_LED, LOW);
      goto connect_to_wifi; // If WiFi is disconnected, reconnect
    }
    if (client.connected() != 1) {
#if DEBUG == true
      Serial.println("WiFiClient disconnected");
#endif
      goto connect_to_host;  // If client is disconnected, reconnect to host
    }
  }
#if DEBUG == true
  Serial.println(" CONNECTED!");
#endif
 // Turn on the GREEN LED to indicate successful connection to WiFi and MQTT
digitalWrite(GREEN_LED, HIGH);
}