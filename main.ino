
//Libraries
#include <DHT.h>
#include <MHZ19.h>
#include <LiquidCrystal.h>

//DHT constants
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//MHZ19 constants
#define RX_PIN A1
#define TX_PIN A0
MHZ19 mhz19(RX_PIN, TX_PIN);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
float ppm; //Stores CO2 value

void setup()
{
    Serial.begin(9600);
    dht.begin();
    lcd.begin(16, 2);
    mhz19.setAutoCalibration(false);
}

void loop()
{
    //Read data and store into variables
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    ppm = mhz19.getPPM(protocol);
    
    //Print data to serial
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%, Temp: ");
    Serial.print(temp);
    Serial.print(" C , CO2: ");
    Serial.println(ppm);
    
    //Print data to lcd
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(hum, 0);
    lcd.print("% T: ");
    lcd.print(temp, 0);
    lcd.setCursor(0, 1);
    lcd.print("CO2: ");
    lcd.print(ppm, 0);
    delay(5000); //Delay 2 sec.
}
