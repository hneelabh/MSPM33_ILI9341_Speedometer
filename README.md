# MSPM33_ILI9341_Speedometer

This project implements a fully functional automotive-style digital speedometer display using TI's MSPM33 microcontroller and ILI9341 TFT display. The system features a visually appealing gauge with animated needle, digital speed readout, and multiple dashboard indicators commonly found in modern vehicles. 

 

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

  
 

LVGL Installation and Configuration 

 

Step 1: Download LVGL 

Either do Git Clone / Download ZIP 

Visit: https://github.com/lvgl/lvgl/releases 

Download v8.3.11 release 

Extract to your project folder 

 

Step 2: Project Structure Setup 

Create the following directory structure: 

 

Step 3: Configure lv_conf.h 

Copy template lv_conf_template.h and save it to the root directory of the project 

Rename it to lv_conf.h 

Enable configuration: Change line 15: 

Change #if 0 to   #if 1  /* Set it to "1" to enable content*/ 

Critical Settings for This Project: 

 

   /* Color depth */ 
   #define LV_COLOR_DEPTH 16 
    
   /* Memory */ 
   #define LV_MEM_SIZE (32U * 1024U) 
    
   /* Display settings */ 
   #define LV_DISP_DEF_REFR_PERIOD 30 
   #define LV_DPI_DEF 130 
    
   /* Enable only needed fonts (CRITICAL FOR BUILD TIME!) */ 
   #define LV_FONT_MONTSERRAT_14 1 
   #define LV_FONT_MONTSERRAT_16 1 
   #define LV_FONT_MONTSERRAT_18 1 
   #define LV_FONT_MONTSERRAT_30 1 
   #define LV_FONT_MONTSERRAT_48 1 
   /* All other fonts = 0 */ 
    
   /* Enable only needed widgets */ 
   #define LV_USE_OBJ 1 
   #define LV_USE_LABEL 1 
   #define LV_USE_IMG 1 
   #define LV_USE_METER 1 
   /* All other widgets = 0 */ 
    
   /* Disable logging */ 
   #define LV_USE_LOG 0 
    
   /* Disable demos and examples */ 
   #define LV_BUILD_EXAMPLES 0 
   #define LV_USE_DEMO_WIDGETS 0 

 

Step 4: Exclude Unnecessary Files 

In Code Composer Studio, exclude the unnecessary directories to prevent long build times: 

Right-click lvgl/demos → Properties 

C/C++ Build → Check "Exclude resource from build" 

Repeat for lvgl/examples 

 

Step 5: Add Include Paths 

In project settings: 

Include paths to add: 
- ${PROJECT_ROOT} 
- ${PROJECT_ROOT}/lvgl 
- ${PROJECT_ROOT}/config 
- ${PROJECT_ROOT}/hardware 
- ${PROJECT_ROOT}/lvgl_port 
- ${PROJECT_ROOT}/ui 

 

Step 6: Verify Installation 

Build the project. If successful, you should see: 

Compiling lv_font_montserrat_14.c   ✓ 
Compiling lv_font_montserrat_16.c   ✓ 
Compiling lv_font_montserrat_18.c   ✓ 
Compiling lv_font_montserrat_30.c   ✓ 
Compiling lv_font_montserrat_48.c   ✓ 
... 
Build complete: ~60 files compiled 
Time: ~1-2 minutes 

 

Common Installation Issues 

Issue 

Solution 

lv_conf.h not found 

Move lv_conf.h to project root, next to lvgl folder 

undefined reference to lv_* 

Add lvgl/src to include paths and source files 

Build takes 15+ minutes 

Disable unused fonts (set to 0) in lv_conf.h 

Display corruption 

Check LV_COLOR_DEPTH matches display (should be 16) 

Compilation errors in demos 

Exclude demos and examples folders from build 

 
