# STM32 HAL USB Driver

## Overview

This project implements a USB driver using the STM32 Hardware Abstraction Layer (HAL). The driver facilitates communication between an STM32 microcontroller and a host system via the USB interface. It supports various USB classes and ensures reliable data transfer and device management. Note that it assumes appropriate USB pins are configured from .ioc via STM32 Cube IDE. Drivers such as `usb_driver.c` must be initialized beforehand. This is another abstraction layer on top of the existing HAL functions. It improves functionality and add simplicity.

## Features

- Supports USB 2.0 communication
- Compatible with multiple USB classes (e.g., CDC, HID, MSC)
- Full-speed USB operation
- Implements control, bulk, interrupt, and isochronous transfer types
- Easy integration with STM32CubeMX generated code
- Configurable endpoint management
- Error handling and recovery mechanisms
- Lightweight and efficient design

## Prerequisites

- STM32 microcontroller (e.g., STM32F4, STM32F1, STM32L4 series)
- STM32CubeMX (for code generation and configuration)
- STM32 HAL library
- Keil MDK, IAR Embedded Workbench, or STM32CubeIDE (for development)

## Installation

1. **Generate Code with STM32CubeMX:**
   - Open STM32CubeMX and create a new project.
   - Select your STM32 microcontroller model.
   - Configure the USB peripheral (e.g., as Device Only).
   - Enable the desired USB class (e.g., CDC for virtual COM port).
   - Generate the initialization code.

2. **Integrate the USB Driver:**
   - Copy the generated USB-related files into your project directory.
   - Ensure the HAL library is included in your project.

3. **Add the USB Driver Source Files:**
   - Copy the provided USB driver source files (`usb_driver.c`, `usb_driver.h`) into your project’s source directory.
   - Include `usb_driver.h` in your main application file.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contact


---
