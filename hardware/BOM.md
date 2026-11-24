# Bill of Materials (BOM) & Unit Cost Breakdown

Target unit economics for the **AgriSense-Edge Sensor Node** and **Community Gateway**. 

Prices are based on batch sourcing (100+ units) via regional component distributors and direct manufacturing channels.

---

## 1. AgriSense-Edge Sensor Node (Per Plot)

| Component | Description / Specification | Qty | Prototype Cost (USD) | Volume Target Cost (USD) |
| :--- | :--- | :---: | :---: | :---: |
| **Microcontroller** | ESP32-WROOM-32D (Dual-core, Ultra-Low Power Coprocessor) | 1 | $4.50 | $3.20 |
| **RF Transceiver** | SX1276 LoRa Module (868 / 915 MHz, +20dBm PA) | 1 | $3.80 | $2.75 |
| **Soil Moisture Sensor** | Corrosion-Resistant Capacitive Soil Moisture Probe v1.2 | 1 | $2.50 | $1.40 |
| **Soil / Ambient Temp Sensor** | DS18B20 Waterproof Probe + DHT22 Ambient | 1 | $3.20 | $2.10 |
| **Solar Power Harvesting** | 5V 1W–5W Monocrystalline Micro Solar Panel (Epoxy sealed) | 1 | $5.50 | $3.50 |
| **Battery Storage** | 3.2V 2500mAh LiFePO4 Cell (2000+ cycle lifespan) | 1 | $6.00 | $4.20 |
| **BMS / Solar Charge Controller** | CN3809 / TP5000 Solar LiFePO4 Charge Controller | 1 | $1.80 | $1.10 |
| **Enclosure & Mount** | IP66 Waterproof Weather-Resistant Junction Box & Stake | 1 | $6.50 | $3.80 |
| **Passives, PCB & Wiring** | Custom 2-layer PCB, decoupling capacitors, terminal blocks | 1 | $5.20 | $2.50 |
| **TOTAL (Sensor Node)** | | | **$39.00** | **$24.55** |

---

## 2. Community Central Gateway & Actuator Hub (Covers up to 20 Plots)

| Component | Description / Specification | Qty | Prototype Cost (USD) | Volume Target Cost (USD) |
| :--- | :--- | :---: | :---: | :---: |
| **Central Controller** | ESP32-S3 or Raspberry Pi Zero 2W | 1 | $9.00 | $7.00 |
| **LoRa Gateway Receiver** | SX1302 or dual SX1276 Multi-Channel Receiver | 1 | $15.00 | $11.00 |
| **Cellular Telemetry** | SIM800L / SIM7600 GSM/GPRS Module (SMS/USSD fallback) | 1 | $6.50 | $4.50 |
| **Solenoid Valve Actuator** | 12V DC Latching Pulse Solenoid Valve (Zero hold current) | 1 | $12.00 | $8.00 |
| **Actuator Driver** | L298N or H-Bridge Latching MOSFET Circuit | 1 | $3.00 | $1.80 |
| **Power Supply** | 12V 10W Solar Panel + 12V 7Ah Sealed Lead-Acid / LiFePO4 | 1 | $22.00 | $16.00 |
| **Weatherproof Enclosure** | IP67 Heavy-duty field enclosure | 1 | $10.00 | $6.50 |
| **TOTAL (Gateway Hub)** | *(Shared across 10–20 farmers)* | | **$77.50** | **$54.80** |

---

## 3. Financial Viability for Smallholders

* **Shared Cost Per Farmer:** When amortized across a 10-farmer cooperative, the gateway cost is under **$5.50 per farmer**.
* **Total Investment Per Plot:** Approximately **$30.00 – $45.00**.
* **Payback Period:** **1 harvesting season (3–4 months)** based on fuel savings (eliminating diesel water pumps) and preventing yield loss from sudden drought.
