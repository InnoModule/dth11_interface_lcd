#include <Wire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        // Pin where DHT11 is connected
#define DHTTYPE DHT11   // Define the sensor type as DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT + LCD Test");
  delay(2000);

  // Initialize DHT Sensor
  dht.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT Ready");
  Serial.println("Setup Complete");
}

void loop() {
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check for failed readings
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Display values on LCD
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print("%    "); // Clear remaining space

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("C    "); // Clear remaining space

    // Print to Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temp: ");
    Serial.print(temperature);
    Serial.println("C");
  }

  delay(2000);  // Wait for 2 seconds before next reading
}

