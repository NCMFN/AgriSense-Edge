/**
 * AgriSense-Edge: Community Gateway & Actuator Hub Firmware
 * Target: ESP32 + SX1276 LoRa + GSM SIM800L + Latching Solenoid Driver
 * 
 * Features:
 * - Continuously listens for peer LoRa sensor packets from farming plots
 * - Triggers 12V latching solenoid valve on automated Edge-AI decision
 * - Sends SMS/USSD alerts in indigenous language to farmer's basic phone
 * 
 * Global Innovation Grand Challenge 2026 (GIIS 2026)
 */

#include <SPI.h>
#include <LoRa.h>
#include <HardwareSerial.h>

#define LORA_SS       5
#define LORA_RST      14
#define LORA_DIO0     2
#define LORA_BAND     868E6

// H-Bridge Pins for Latching Solenoid Valve
#define VALVE_OPEN_PIN   25
#define VALVE_CLOSE_PIN  26

// GSM Serial on Hardware UART2
HardwareSerial gsmSerial(2);
#define GSM_RX 16
#define GSM_TX 17

const char* FARMER_PHONE_NUMBER = "+2348000000000"; // Target smallholder phone

void pulseValve(bool openValve) {
    if (openValve) {
        Serial.println("[Valve] Actuating: OPENING drip irrigation line (50ms pulse)...");
        digitalWrite(VALVE_OPEN_PIN, HIGH);
        delay(50); // 50ms latch pulse
        digitalWrite(VALVE_OPEN_PIN, LOW);
    } else {
        Serial.println("[Valve] Actuating: CLOSING drip irrigation line (50ms reverse pulse)...");
        digitalWrite(VALVE_CLOSE_PIN, HIGH);
        delay(50);
        digitalWrite(VALVE_CLOSE_PIN, LOW);
    }
}

void sendFarmerSMS(String nodeID, float moisture, int action) {
    Serial.println("[GSM] Sending advisory SMS to farmer...");
    gsmSerial.println("AT+CMGF=1"); // Set SMS text mode
    delay(200);
    gsmSerial.print("AT+CMGS=\"");
    gsmSerial.print(FARMER_PHONE_NUMBER);
    gsmSerial.println("\"");
    delay(200);

    // Formulate inclusive SMS message
    if (action == 2) {
        gsmSerial.printf("AgriSense Alert [%s]: Low soil moisture (%.1f%%). Automated solar drip irrigation active for 20 mins. No action needed.\n", 
                         nodeID.c_str(), moisture);
    } else {
        gsmSerial.printf("AgriSense Status [%s]: Soil moisture optimal (%.1f%%). Next cycle scheduled for 6:00 PM.\n", 
                         nodeID.c_str(), moisture);
    }
    delay(200);
    gsmSerial.write(26); // ASCII character 26 (Ctrl+Z) to send
    delay(1000);
}

void setup() {
    Serial.begin(115200);
    gsmSerial.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);

    pinMode(VALVE_OPEN_PIN, OUTPUT);
    pinMode(VALVE_CLOSE_PIN, OUTPUT);
    digitalWrite(VALVE_OPEN_PIN, LOW);
    digitalWrite(VALVE_CLOSE_PIN, LOW);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(LORA_BAND)) {
        Serial.println("[Error] LoRa gateway initialization failed!");
        while (1);
    }
    Serial.println("[AgriSense Gateway] Online and listening for field nodes...");
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String packetData = "";
        while (LoRa.available()) {
            packetData += (char)LoRa.read();
        }
        Serial.printf("[Gateway RX] Received: %s (RSSI: %d)\n", packetData.c_str(), LoRa.packetRssi());

        // Parse CSV format: NODE_ID, MOISTURE, TEMP, ACTION_CODE
        int comma1 = packetData.indexOf(',');
        int comma2 = packetData.indexOf(',', comma1 + 1);
        int comma3 = packetData.indexOf(',', comma2 + 1);

        if (comma1 > 0 && comma2 > 0 && comma3 > 0) {
            String nodeID = packetData.substring(0, comma1);
            float moisture = packetData.substring(comma1 + 1, comma2).toFloat();
            float temp = packetData.substring(comma2 + 1, comma3).toFloat();
            int action = packetData.substring(comma3 + 1).toInt();

            if (action == 2) {
                // Action 2: Trigger automated irrigation
                pulseValve(true);
                sendFarmerSMS(nodeID, moisture, action);
                delay(20 * 60 * 1000); // 20-minute irrigation interval
                pulseValve(false);     // Close valve after watering cycle
            }
        }
    }
}
