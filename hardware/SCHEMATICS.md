# Hardware Schematics & Wiring Pinouts

This document outlines the pinout connections, power architecture, and electrical schematics for the **AgriSense-Edge Sensor Node** and the **Community Actuator Gateway**.

---

## 1. Sensor Node Wiring Pinout (ESP32 Dev Module)

```
                       +-------------------+
                       |    ESP32-WROOM    |
                       +-------------------+
      Capacitive Sensor |                   |
      [VCC] ----------> | 3.3V              |
      [GND] ----------> | GND               |
      [AOUT] ---------> | GPIO 36 (ADC1_CH0)|
                        |                   |
      DS18B20 Temp Probe|                   |
      [VCC] ----------> | 3.3V              |
      [GND] ----------> | GND               |
      [DQ] -----------> | GPIO 4 (4.7k Pull)|
                        |                   |
      LoRa SX1276 Module|                   |
      [NSS / CS] -----> | GPIO 5            |
      [MOSI] ---------> | GPIO 23           |
      [MISO] ---------> | GPIO 19           |
      [SCK] ----------> | GPIO 18           |
      [RST] ----------> | GPIO 14           |
      [DIO0] ---------> | GPIO 2            |
      [3.3V / GND] ---> | 3.3V / GND        |
                        +-------------------+
```

---

## 2. Power Consumption & Energy Budget

To achieve continuous, maintenance-free multi-year off-grid operation, the node operates in an aggressive cyclic duty-cycle state:

### Operational Profile:
* **Deep Sleep Duration:** 28 minutes and 50 seconds (1730 s).
* **Wake-Up & Sensing:** 5 seconds (Sensor excitation, ADC sampling, calibration).
* **TinyML Inference:** 15 milliseconds (Executing soil moisture depletion curve).
* **LoRa Transmission:** 80 milliseconds (+17 dBm packet transmission).
* **Total Active Window:** ~6 seconds every 30 minutes (0.33% duty cycle).

### Power Consumption Metrics:
| State | Current Draw | Voltage | Power |
| :--- | :--- | :--- | :--- |
| **Deep Sleep** | 22 µA | 3.3 V | 0.072 mW |
| **Sensor Read** | 18 mA | 3.3 V | 59.4 mW |
| **TinyML Inference** | 45 mA | 3.3 V | 148.5 mW |
| **LoRa TX (+17dBm)** | 110 mA | 3.3 V | 363.0 mW |
| **Average Hourly Current** | **~0.15 mA** | 3.3 V | **0.495 mWh/hour** |

### Battery Autonomy Analysis:
* **Battery Capacity:** 2500 mAh @ 3.2V = 8,000 mWh.
* **Without Solar Recharging (Zero Sunlight):** $8000 \text{ mWh} / (0.495 \text{ mWh/hr} \times 24 \text{ hr}) \approx \mathbf{673\text{ days}}$ theoretical battery lifespan.
* **With 5W Solar Panel:** The node reaches **100% net-positive energy equilibrium** with under 15 minutes of diffused ambient daylight per day.

---

## 3. Community Gateway & Solenoid Actuator Pinout

```
                       +-------------------+
                       |    ESP32 Gateway  |
                       +-------------------+
      LoRa SX1276       |                   |
      [SPI Lines] ----> | Standard SPI Pins |
                        |                   |
      SIM800L GSM       |                   |
      [TX] -----------> | GPIO 16 (RX2)     |
      [RX] -----------> | GPIO 17 (TX2)     |
      [VCC (4.0V)] ---> | External Buck Reg |
                        |                   |
      H-Bridge Latching |                   |
      [IN1] ----------> | GPIO 25           |
      [IN2] ----------> | GPIO 26           |
                        +-------------------+
                                  │
                                  ▼
               [12V Latching Solenoid Pulse Valve]
               * Requires 50ms pulse to open (0W standby)
               * Requires 50ms reverse pulse to close
```
