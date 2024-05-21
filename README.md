# ESP32 Energy Meter

Welcome to the official repository for the ESP32 Energy Meter, an energy monitoring project developed by Elektor Labs. This repository hosts all the necessary design files, code, and documentation to build and deploy a safe energy meter using the ESP32-S3 microcontroller.

## Project Overview

The ESP32 Energy Meter utilizes the Espressif ESP32-S3 microcontroller and the ATM90E32AS IC from Microchip for precise energy measurement across single and three-phase systems. This version includes significant safety and functionality enhancements, including a transformer-based power supply and modularity for diverse applications.

## Features

- **High Precision:** Uses ATM90E32AS IC for accurate energy data.
- **Enhanced Safety:** Transformer-based power reduces direct exposure to high voltages.
- **Flexible Configuration:** Supports both single-phase and three-phase installations.
- **Smart Home Integration:** Easily integrates with Home Assistant for advanced energy management.
- **Customizable Firmware:** Includes ESPHome YAML configurations for easy adaptation and updates.

## Repository Contents

- `/hardware` - Electronic schematic files.
- `/hardware` - PCB design files suitable for manufacturing.
- `/src/ESPHome` - ESPHome YAML configuration files.

## Getting Started

### Prerequisites

Ensure you have the following components :
- ESP32-S3 module
- ATM90E32AS IC
- Step-down transformer (220V AC to 12V AC)
- Essential passive components (resistors, capacitors)
- Tools for PCB assembly and soldering

### Setup Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ElektorLabs/esp32-energymeter.git
   ```
2. **PCB Assembly:**
   - Refer to the `/hardware` directory and manufacture the PCB using the provided design files.
   - Solder the components onto the PCB as per the layout and schematic details in the `/Schematics` folder.

3. **Firmware Installation:**
   - Navigate to the `/src/ESPHome` directory.
   - Update the YAML file with your specific network details and preferences.
   - Flash the firmware to the ESP32-S3 using ESPHome through the command line or ESPHome Dashboard.

4. **Integrate with Home Assistant:**
   - Follow the integration guide in the article to connect the energy meter to Home Assistant.
   - Monitor and manage your energy consumption directly through the Home Assistant interface.

## Calibration and Testing

- After assembly, perform a calibration check as described in the article to ensure accuracy.
- Test the device under different load conditions to verify the setup and adjust the calibration if necessary.

## Contributing

Your contributions are welcome! If you have enhancements, fixes, or improvements, please fork this repository and submit a pull request with your changes. For substantial modifications or new features, please open an issue to discuss them first.

## License

This project is distributed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Thanks to Espressif Systems for the ESP32 technology.
- Thanks to Microchip for the energy measurement IC.
- Gratitude to all community members who have contributed to refining this project.

## Contact

For further inquiries or support, feel free to reach out through GitHub issues or the project discussion board.

---
