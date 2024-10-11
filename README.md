# Dynamic Clock Menu System with STM32F401RE Nucleo Board and FreeRTOS

## Overview
This project implements a dynamic clock menu system on the STM32F401RE Nucleo board, integrating various peripherals such as an LCD, 7-segment display, RTC, and USB HID-Keyboard. The system is optimized using FreeRTOS for task management and resource synchronization, allowing efficient multitasking and responsive user input.

## Features
- **LCD Display**: Displays the menu options to view/update date and time.
- **7-Segment Display**: Displays the date or time whichever is chosen.
- **Real-Time Clock (RTC)**: Maintains accurate time even when the system is off.
- **USB HID-Keyboard**: Allows user interaction to navigate through the menu system and update the clock.
- **FreeRTOS Integration**: Optimizes performance through task scheduling, synchronization, and low-power modes.
  
## Project Structure
The project is structured around FreeRTOS tasks to ensure efficient operation and proper peripheral handling.

### Main Functionalities
- **Clock Display**: Continuously updates the LCD and 7-segment displays with current time.
- **Menu Navigation**: Users can interact with the menu via a USB HID keyboard to set or change the time, toggle display modes, and access additional features.
- **Peripheral Management**: FreeRTOS tasks are used to handle individual peripherals, ensuring smooth operation and responsiveness.

## Hardware Requirements
- **STM32F401RE Nucleo Board**
- **16x2 LCD** (I2C or Parallel)
- **6-Digit 7-Segment Display**
- **Real-Time Clock (RTC) Module**
- **USB HID-Keyboard**

## Software Requirements
- **STM32CubeIDE**: Development environment for STM32 microcontrollers.
- **FreeRTOS**: Real-time operating system for scheduling and multitasking.
- **STM32 HAL Libraries**: For hardware abstraction and peripheral control.
- **USB HID Libraries**: To support keyboard input.
- **LCD & 7-Segment Display Drivers**: For interfacing with the display hardware.

## FreeRTOS Features
- **Task Scheduling**: Each peripheral (LCD, 7-segment, RTC, USB HID) is managed by a dedicated task, allowing non-blocking execution.
- **Task Priorities**: Critical tasks like RTC updates are assigned higher priority.
- **Inter-task Communication**: Queues are used to pass data between tasks, such as sending time data from the RTC task to the display task.
- **Task Synchronization**: Mutexes ensure that shared resources (like the display) are accessed safely.

## Setup and Installation
- Unzip the menu.zip file and run it in STM32CubeIDE. Use STM32F401RE Nucleo Board to run the code.
