#include <DHT.h>

// Pin where the sensor is connected
#define DHTPIN 2
#define DHTTYPE DHT11   // Change to DHT22 if you're using a DHT22 sensor

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  dht.begin();         // Initialize the sensor
}

void loop() {
  delay(2000);  // Wait for 2 seconds before reading again

  // Read the temperature in Celsius
  float temperature = dht.readTemperature();
  Serial.print("Temperature: ");  // Text label
    Serial.println(temperature); 

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from sensor");
    return;
  }

  // Send the temperature value to the Serial Monitor
  Serial.println(temperature);

  // You can add additional data (e.g., humidity, if needed)
  // float humidity = dht.readHumidity();
  // Serial.println(humidity);
}
