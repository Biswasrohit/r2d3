# R2D3: Dual-Axis Solar Tracker Inspired by R2D2

A proof-of-concept solar tracker that automatically orients a photovoltaic panel in two axes (azimuth & elevation) to maximize sunlight exposure. Built with an Arduino Uno, hobby servos, a solar panel sensor, and custom PLA-printed parts modeled in SolidWorks.

---

## 📖 Table of Contents

1. [Project Overview](#project-overview)  
2. [Key Features](#key-features)  
3. [Hardware Components](#hardware-components)  
4. [Software & Firmware](#software--firmware)  
5. [CAD & 3D Prints](#cad--3d-prints)  
6. [Getting Started](#getting-started)  
7. [Usage](#usage)  
8. [Results & Performance](#results--performance)  
9. [Future Improvements](#future-improvements)  
10. [References](#references)  
11. [License](#license)  

---

## Project Overview

This project implements a compact, dual-axis solar tracker that:

- **Senses** sunlight intensity using a small solar panel as both a sensor and energy source.  
- **Adjusts** panel orientation in real time via two servo motors (one for horizontal rotation, one for vertical tilt).  
- **Locks** onto the brightest direction using a dynamic, local‐scan algorithm—no full 180° sweep on each update.  
- **Demonstrates** how mechanical design, electronics integration, and firmware must co-evolve in a hands-on engineering build.

Inspired by the droid **R2D2**, our “R2D3” tracker combines playful form with practical function.

---

## Key Features

- **Dual-Axis Control**: Independent azimuth & elevation tracking.  
- **Analog Feedback**: Reads voltage from the panel (A0) to detect light intensity.  
- **Dynamic Local Scan**: Reduces scan range for faster, more efficient tracking.  
- **PLA 3D-Printed Enclosure**: Renewable polylactic acid parts customized in SolidWorks.  
- **Modular Design**: Clear separation between electronics housing and moving head.

---

## Hardware Components

| Component                  | Qty  | Notes                                    |
|----------------------------|:----:|------------------------------------------|
| Arduino Uno R3             | 1    | Main controller                          |
| Servo motor (horizontal)   | 1    | 180° range, ~2 kg·cm torque              |
| Servo motor (vertical)     | 1    | 180° range, ~2 kg·cm torque              |
| Mini solar panel (sensor)  | 1    | Outputs analog voltage proportional to light |
| PLA filament               | —    | Polylactic acid for 3D prints            |
| Jumper wires & connectors  | —    | Power, ground, data routing              |
| USB-A cable                | 1    | For Arduino power & programming          |
| Popsicle sticks & glue     | —    | Quick alignment fix for print tolerances |

> **Note:** PLA stands for **polylactic acid**, a biodegradable thermoplastic derived from renewable resources.

---

## Software & Firmware

- **Arduino Sketch**  
  - `readVoltage()`: Reads and maps panel voltage (A0 → 0–5 V).  
  - `findMaxPosition()` / `trackLightLocally()`: Local-scan routines to find the brightest “hotspot.”  
  - Safety checks to prevent over-rotation beyond physical limits.

- **Dependencies**  
  - Arduino IDE (v1.8+) or Arduino CLI  
  - No external libraries required (uses core Servo & Arduino APIs)

---

## 3D Prints

- **SolidWorks Models**  
  - `CAD/StorageCube.SLDPRT` – Electronics housing with wiring pass-through  
  - `CAD/UpperSphere.SLDPRT` – Rotating head to support the panel  
  - `CAD/Base.SLDPRT` – Base
  - `CAD/TopLid.SLDPRT` - Top Lid

> **Tip:** Print at 0.2 mm layer height with 20% infill for a balance of strength and speed.

---

## Getting Started

Follow these steps to set up and run your R2D3 solar tracker:

1. **Clone the repository**  
    git clone https://github.com/Biswasrohit/r2d3.git                 
    cd r2d3

3. **3D-print the parts**  
    - Slice the files in STL/ with your preferred slicer  
    - Recommended settings: PLA, 0.2 mm layer height, 20 % infill, 60 °C bed, 200 °C nozzle

4. **Assemble the hardware**  
    - Secure the horizontal servo into LowerBase.stl  
    - Thread wiring through the base passthrough hole  
    - Attach the secondary cylindrical base and upper hemisphere (UpperHemisphere.stl) to the horizontal horn  
    - Mount the vertical servo and solar panel in the hemisphere using the popsicle-stick armature

5. **Wire the electronics**  
    - Power servos from Arduino 5 V & GND; signal pins to D9 (horizontal) and D10 (vertical)  
    - Connect panel’s positive lead to A0 and negative lead to GND  
    - Tidy cables through built-in channels

6. **Upload the firmware**  
    - Open firmware/R2D3_Tracker.ino in the Arduino IDE (v1.8+)  
    - Select “Arduino Uno” and the correct serial port  
    - Click “Upload”

7. **Power and test**  
    - Plug Arduino into USB-A (PC or power bank)  
    - Observe initial local scan, then place under a lamp or sunlight—panel should smoothly follow the brightest spot

---

## Usage

- **Initial Scan:** On power-up, performs a limited sweep around last known position to find the brightest direction  
- **Continuous Tracking:** Every 5 seconds (configurable in firmware), updates azimuth/elevation within a ±30° “hotspot” zone  
- **Safety Limits:**  
    - Azimuth: –90° to +90°  
    - Elevation: 25° to 155°

Modify these ranges in `trackAzimuth()` and `trackElevation()` to suit your hardware.

---

## Results & Performance

- **Dual-Axis Operation:** Azimuth (±90°) and elevation (25–155°) confirmed  
- **Response Time:** < 2 s to reorient within a 30° hotspot  
- **Accuracy:** Typically within 10–15° of peak illumination  
- **Robustness:** Maintains lock under partial occlusion and changing light

Full data and graphs in docs/FinalReport.pdf.

---

## Future Improvements

1. **Higher-Torque Actuators**  
   Swap to geared or brushless servos for larger panels  
2. **Custom PCB**  
   Integrate power regulation and cleaner signal routing  
3. **Refined CAD**  
   Realign parts to eliminate shim workarounds  
4. **IoT Telemetry**  
   Add an ESP32 for remote monitoring, data logging, and web dashboard  
5. **Weatherproofing**  
   Design sealed enclosures for outdoor deployment

---

## References

- Arduino® UNO R3 Product Reference Manual  
- Banerjee, R. (2015). *Solar tracking system*. IJSRP, 5(3).  
- Deekshith, K. et al. (2015). *Solar tracking system*. IJSER, 6(9).  
- Zhang, Y., Li, X., & Wang, J. (2024). *Advancements in renewable energy technologies*. Renewable Energy Reports, 10(2), 123–145.

---

## License

This project is released under the **MIT License**. See LICENSE for details.
