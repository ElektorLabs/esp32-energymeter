
#define DEBUG true  // Make this false if Serial Monitor is not required.

#define WIFISSID "xxxx"
#define WIFIPASSWORD "xxxx"

#define HOMEASSISTANT_IP "xxxx"
#define DEVICE_NAME "esp32-energymeter"
#define USER_ID "xxxx"
#define PASSWORD "xxxx"

/***** CALIBRATION SETTINGS *****/
/* 
 * 4485 for 60 Hz
 * 389 for 50 Hz
 */

#define LINEFREQ 389

/* 
 * 0 for 1x (CTs up to 60mA/720mV)
 * 21 for 2x (CTs up to 30mA/360mV)
 * 42 for 4x (CTs up to 15mA/180mV)
 */
#define PGA_GAIN 21

#define VOLTAGE_GAIN 3920

/*
 * 25498 - SCT-013-000 100A/50mA
 * 39473 - SCT-016 120A/40mA
 */
 
#define GAIN_CT_A 39473
#define GAIN_CT_B 39473
#define GAIN_CT_C 39473

#define CS_PIN 10
/*
  12 - CLK
  13 - MISO
  11 - MOSI
*/ 
#define GREEN_LED 47
