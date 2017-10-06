
//Libraries
#include <DHT.h>
#include <MQ135.h>
#include <LiquidCrystal.h>

//Constants
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define MQ135_PIN A0
MQ135 mq135(MQ135_PIN);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float ppm;

void setup()
{
    Serial.begin(9600);
    dht.begin();
    lcd.begin(16, 2);
}

void loop()
{
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    ppm = mq135.getCorrectedPPM(temp, hum);
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%, Temp: ");
    Serial.print(temp);
    Serial.print(" C , CO2: ");
    Serial.println(ppm);
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(hum, 0);
    lcd.print("% T: ");
    lcd.print(temp, 0);
    lcd.setCursor(0, 1);
    lcd.print("CO2: ");
    lcd.print(ppm, 0);
    delay(2000); //Delay 2 sec.
}
