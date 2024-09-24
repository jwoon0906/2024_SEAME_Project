#include <TimerOne.h>
#include "mcp_can.h"
#include <SPI.h>

// Include the TimerOne Library from Paul Stoffregen
#include "TimerOne.h"
 
// Constants for Interrupt Pins
const byte MOTOR1 = 3;  // Motor 1 Interrupt Pin - INT 0
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);

// Integers for pulse counters
volatile unsigned int counter1 = 0;  // Use volatile because it's modified in an ISR
 
// Float for number of slots in encoder disk
float diskslots = 20;  // Change to match value of encoder disk
float filetered = 0.0;
unsigned long lastTime = 0;
float rpm = 0;  // Variable to store calculated RPM
// Kalman Filter variables
float Q = 5.0;  // Increased process noise covariance for faster response
float R = 5.0;  // Decreased measurement noise covariance for faster response
float P = 1.0;  // Estimation error covariance
float K = 0.0;  // Kalman gain
float x_est_last = 0.0;  // Last estimated RPM
float kalmanFilter(float rpm_measured) {
  // Predict phase: x_est_last remains the same (no dynamic system)
  P = P + Q;  // Prediction of error covariance

  // Update phase
  K = P / (P + R);  // Kalman gain
  float x_est = x_est_last + K * (rpm_measured - x_est_last);  // Estimate the current RPM
  P = (1 - K) * P;  // Update the error covariance

  // Save the estimate for the next round
  x_est_last = x_est;

  return x_est;
}

// Interrupt Service Routines
void ISR_count1()  
{
  counter1++;  // increment Motor 1 counter value
} 
 
void setup() 
{
  Serial.begin(115200);
  pinMode(MOTOR1, INPUT_PULLUP);  // Set the motor pin as input with pullup resistor
  attachInterrupt(digitalPinToInterrupt(MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High
  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ))        // init can bus : baudrate = 500k
  {
      Serial.println("CAN BUS Shield init fail");
      Serial.println(" Init CAN BUS Shield again");
      delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
  CAN.setMode(MCP_NORMAL);
}
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void loop() {
  unsigned long currentTime = millis();

  // Update and calculate RPM every second (1000 ms)
  if (currentTime - lastTime >= 1000) {
    // Calculate RPM

    // Print RPM to Serial Monitor
    filetered = kalmanFilter(counter1);

    // Scale RPM to 0-255 range for 1 byte transmission

    // Prepare CAN message
    //stmp[0] = scaledRPM;  // Send scaled RPM as 1 byte
    stmp[0] = filetered;
    stmp[1] = int(filetered * 100) % 100;
    CAN.sendMsgBuf(0x123, 0, 8, stmp);
    Serial.println(filetered);
    // Reset the counter for the next calculation
    counter1 = 0;

    // Update lastTime to the current time
    lastTime = currentTime;
  }
}
