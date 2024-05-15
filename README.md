# ESP32 Energy Meter

Welcome to the official repository for the ESP32 Energy Meter project, developed by Elektor Labs. This project is designed to provide a reliable, efficient, and user-friendly energy metering solution using the ESP32 microcontroller platform. 

## Project Overview

The ESP32 Energy Meter leverages the capabilities of the Espressif ESP32-S3 microcontroller to deliver precise energy measurement and management functionalities. This repository contains all the necessary resources including the schematic, PCB layout, and ESPHome YAML code to help you build and customize your own energy meter.

## Features

- **High Accuracy Measurement:** Utilizes the ATM90E32AS IC for precise energy measurement.
- **Safety Design:** Features transformer-based power supply for enhanced safety and isolation.
- **Modularity:** Offers flexibility with easy integration options for both single-phase and three-phase systems.
- **User-Friendly Interface:** Integrates with Home Assistant for a seamless user experience.
- **Customizable Firmware:** ESPHome YAML files provided for easy customization and updates.

## Repository Contents

- `/hardware` - Electronic schematic files for the ESP32 Energy Meter.
- `/hardware` - Printed Circuit Board design files for fabrication.
- `/src/ESPHome` - YAML configuration files for running the energy meter on ESPHome.

## Getting Started

To start building your ESP32 Energy Meter, clone this repository and review the documentation provided. Ensure you have the required components and tools listed.

```bash
git clone https://github.com/ElektorLabs/esp32-energymeter.git
```

## Integration with Home Assistant

This project is designed to work seamlessly with Home Assistant. After assembling your device, follow the configuration steps in the `/src` directory to integrate the energy meter with your Home Assistant setup.

## Contributing

We welcome contributions to the ESP32 Energy Meter project. If you have improvements or bug fixes, please feel free to fork this repository and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Acknowledgments

- Espressif Systems for the ESP32 microcontroller.
- ATMEL for the ATM90E32AS energy measurement IC.
- All contributors and community members who have provided feedback and suggestions.

Thank you for supporting the ESP32 Energy Meter project. We hope this project will be a valuable tool in your energy management endeavors!

---
