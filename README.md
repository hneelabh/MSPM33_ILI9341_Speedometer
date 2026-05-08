Overview 

 

This project implements a fully functional automotive-style digital speedometer display using an MSP microcontroller and ILI9341 TFT display. The system features a visually appealing gauge with animated needle, digital speed readout, and multiple dashboard indicators commonly found in modern vehicles. 

 

Key Features 

Speedometer Gauge: 0-160 km/h range with animated needle 

Digital Speed Display: Large, easy-to-read numerical speed indicator 

Turn Signal Indicators: Left/right arrow indicators with blinking animation 

Fuel Gauge: Vertical bar display with color-coded levels (red to green) 

Odometer: Trip meter showing accumulated distance 

Dashboard Icons:  

Bluetooth connectivity status 

Check engine warning light 

Gear position indicator (P/R/N/D) 

Modular Code Architecture: Easy to maintain and extend 
 

Hardware and Software Specifications 

 

Hardware Requirements 

Microcontroller 

Model: TI MSPM33-C321x-Q1 

Display 

Model: ILI9341 TFT LCD 

Resolution: 320×240 pixels 

Color Depth: RGB565 (16-bit color) 

Interface: SPI 

Size: 2.4" diagonal 

 

Software Requirements 

Development Environment 

IDE: Code Composer Studio (CCS) v12.0 or later 

Compiler: TI ARM Compiler 

Libraries and Dependencies 

LVGL: v8.3.11 

TI Driverlib: For MSP peripheral configuration 

Custom Drivers: SPI interface, TFT driver (included in project) 

Development Tools 

Debugger: XDS110 (TI debugger) 

 

Memory Usage (by project's .c files alone) 

 

Component 

Size 

Code (Flash) 

~80-100 KB 

LVGL Library 

~60 KB 

Graphics Buffers (RAM) 

~19 KB (dual buffering) 

Static Data 

~5 KB 

Stack/Heap 

~8 KB 

Total Flash 

~150 KB 

Total RAM 

~32 KB 

 
Hardware Connections - Pin Configuration 

 

MSPM33 

ILI9341 Display 

3.3V   

VCC 

GND 

GND 

P1.4 (SCLK) 

SCK 

P1.5 (MOSI) 

MOSI 

P1.6 (MISO) 

MISO 

P2.0 

CS 

P2.1 

DC 

P2.2 

RESET 

P1.0 

LED 

  

