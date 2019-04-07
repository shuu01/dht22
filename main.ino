//Libraries
#include <DHT.h>
#include <MHZ19.h>
#include <LiquidCrystal.h>

//Constants
#define DHTPIN 10
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define RX_PIN A1
#define TX_PIN A0
MHZ19 mhz19;

//define buttonPin 1
#define ledPin 2

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Variables
int ppm;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int timeout = 180; //seconds
int del = 5000; //milliseconds

void setup()
{
    Serial.begin(9600);
    mhz19.begin(RX_PIN, TX_PIN);
    mhz19.setAutoCalibration(false);
    dht.begin();
    lcd.begin(16, 2);
}

void loop()
{
    //Read data and store it into variables
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    ppm = mhz19.getPPM();
    
    //Print data to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%, Temp: ");
    Serial.print(temp);
    Serial.print(" C, CO2: ");
    if (timeout > 0) {
      timeout -= del/1000;
      Serial.println("heating...");
    }
    else
    {
      Serial.println(ppm);
    }

    //Print data to lcd
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(hum, 0);
    lcd.print("%");
    lcd.print(" T: ");
    lcd.print(temp, 0);
    lcd.setCursor(0, 1);
    lcd.print("CO2: ");
    if (timeout > 0) {
      timeout -= del/1000;
      lcd.print("heating...");
    }
    else
    {
      lcd.print(ppm);
    }

    delay(del); //Delay 5 sec.
}
