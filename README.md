# MSPM33 ILI9341 Digital Speedometer

## Overview 
This project implements a fully functional **automotive-style digital speedometer** display using TI's MSPM33 microcontroller and an ILI9341 TFT display. The system features a visually appealing gauge with an animated needle, a digital speed readout, and multiple dashboard indicators commonly found in modern vehicles. 

## Key Features 
* **Speedometer Gauge:** 0-160 km/h range with an animated needle.
* **Digital Speed Display:** Large, easy-to-read numerical speed indicator.
* **Turn Signal Indicators:** Left/right arrow indicators with blinking animation.
* **Fuel Gauge:** Vertical bar display with color-coded levels (red to green).
* **Odometer:** Trip meter showing accumulated distance.
* **Dashboard Icons:**  
  * Bluetooth connectivity status
  * Check engine warning light
  * Gear position indicator (P/R/N/D)
* **Modular Code Architecture:** Easy to maintain and extend.

## Hardware and Software Specifications 

### Hardware Requirements 
* **Microcontroller:** TI MSPM33-C321x-Q1 
* **Display:** ILI9341 TFT LCD 
  * **Resolution:** 320×240 pixels 
  * **Color Depth:** RGB565 (16-bit color) 
  * **Interface:** SPI 
  * **Size:** 2.4" diagonal 

### Software Requirements 
* **IDE:** Code Composer Studio (CCS) v12.0 or later 
* **Compiler:** TI ARM Compiler 
* **Debugger:** XDS110 (TI debugger) 
* **Libraries and Dependencies:**
  * **LVGL:** v8.3.11 
  * **TI Driverlib:** For MSP peripheral configuration 
  * **Custom Drivers:** SPI interface, TFT driver (included in project) 

## Memory Usage 
*(Based on the project's `.c` files alone)*

| Component | Size |
| :--- | :--- |
| **Code (Flash)** | ~80-100 KB |
| **LVGL Library** | ~60 KB |
| **Graphics Buffers (RAM)** | ~19 KB (dual buffering) |
| **Static Data** | ~5 KB |
| **Stack/Heap** | ~8 KB |
| **Total Flash** | ~150 KB |
| **Total RAM** | ~32 KB |

## Pin Configuration 

| MSPM33 Pin | ILI9341 Display |
| :--- | :--- |
| 3.3V | VCC |
| GND | GND |
| P1.4 (SCLK) | SCK |
| P1.5 (MOSI) | MOSI |
| P1.6 (MISO) | MISO |
| P2.0 | CS |
| P2.1 | DC |
| P2.2 | RESET |
| P1.0 | LED |

---

## LVGL Installation and Configuration 

### Step 1: Download LVGL 
1. Visit the [LVGL Releases Page](https://github.com/lvgl/lvgl/releases).
2. Download the **v8.3.11** release (via Git Clone or Download ZIP).
3. Extract the contents to your project folder.

### Step 2: Project Structure Setup 
Ensure your project directory structure looks similar to this:
```text
project_root/
├── lvgl/
├── config/
├── hardware/
├── lvgl_port/
├── ui/
└── lv_conf.h
```

### Step 3: Configure `lv_conf.h` 
1. Copy the template `lv_conf_template.h` and save it to the root directory of the project.
2. Rename it to `lv_conf.h`.
3. Enable the configuration by changing line 15:
   ```c
   #if 1  /* Set it to "1" to enable content */ 
   
```
4. **Critical Settings for This Project:** Apply the following configurations to optimize performance and build time.

```c
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
/* Set all other fonts to 0 */ 

/* Enable only needed widgets */ 
#define LV_USE_OBJ 1 
#define LV_USE_LABEL 1 
#define LV_USE_IMG 1 
#define LV_USE_METER 1 
/* Set all other widgets to 0 */ 

/* Disable logging */ 
#define LV_USE_LOG 0 

/* Disable demos and examples */ 
#define LV_BUILD_EXAMPLES 0 
#define LV_USE_DEMO_WIDGETS 0 
```

### Step 4: Exclude Unnecessary Files 
In Code Composer Studio, exclude the unnecessary directories to prevent long build times: 
1. Right-click `lvgl/demos` → **Properties** 
2. Navigate to **C/C++ Build** → Check **"Exclude resource from build"** 
3. Repeat this process for `lvgl/examples`.

### Step 5: Add Include Paths 
In your CCS project settings, add the following include paths: 
* `${PROJECT_ROOT}` 
* `${PROJECT_ROOT}/lvgl` 
* `${PROJECT_ROOT}/config` 
* `${PROJECT_ROOT}/hardware` 
* `${PROJECT_ROOT}/lvgl_port` 
* `${PROJECT_ROOT}/ui` 

### Step 6: Verify Installation 
Build the project. If successful, your compiler output should look like this: 
```text
Compiling lv_font_montserrat_14.c   ✓ 
Compiling lv_font_montserrat_16.c   ✓ 
Compiling lv_font_montserrat_18.c   ✓ 
Compiling lv_font_montserrat_30.c   ✓ 
Compiling lv_font_montserrat_48.c   ✓ 
... 
Build complete: ~60 files compiled 
Time: ~1-2 minutes 
```

---

## Common Installation Issues 

| Issue | Solution |
| :--- | :--- |
| `lv_conf.h` not found | Move `lv_conf.h` to the project root, next to the `lvgl` folder. |
| `undefined reference to lv_*` | Add `lvgl/src` to your include paths and source files. |
| Build takes 15+ minutes | Disable unused fonts (set to 0) in `lv_conf.h`. |
| Display corruption | Check that `LV_COLOR_DEPTH` matches the display (should be 16). |
| Compilation errors in demos | Ensure the `demos` and `examples` folders are excluded from the build. |
