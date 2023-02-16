
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Enter SSID";
char pass[] = "Enter password";

#include <ESP32Servo.h>
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPLFNHId3V6"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "qivhMtvejmj7nPfGsgxVjg3J3o4Pc061"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int steer = 90; 
int speed = 1000;


Servo bldc,steering; 

// This function will be called every time Slider Widget in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1) //bldc
{
  speed = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("Speed PWM value is: ");
  Serial.println(speed);
}

// This function will be called every time Slider Widget in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4) //steering
{
  steer = param.asInt();  // assigning incoming value from pin V4 to a variable
  Serial.print("Steer Slider value is: ");
  Serial.println(steer);
}

void setup()
{
  // Debug console
    Serial.begin(115200);
  bldc.attach(15, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  steering.attach(23,MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  bldc.writeMicroseconds(speed);
  steering.write(steer);
}
