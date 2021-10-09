
/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"
//DHT dht22;
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!
//#define DHTPIN    2         // DHT22 data pin is connected to Arduino analog pin 0
//#define DHTTYPE   DHT22      // DHT22 sensor is used
 //(DHTPIN, DHTTYPE);  // configure DHT library
 
char temperature[] = "000.0 C";
char humidity[]    = "000.0 %";
int j=0;
//int prev=0;
//int pres=0;
int RH ;
int Temp ;
DHT dht22;
void setup()
{
 
 // pinMode(10 ,INPUT);
  //delay(1000);  // wait 1 second
  dht22.setup(2) ;
  delay(1000);
   // read humidity
  // = dht22.getHumidity() * 10;
  // read temperature in degree Celsius
  // = dht22.getTemperature() * 10;
  // initialize the display
  
  display.begin();
  display.setContrast(60);
  // initialize the DHT library
 // dht22.begin();
/*  
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
 
  display.clearDisplay();   // clear the screen and buffer
  display.display();
 
  display.drawFastHLine(0, 8, display.width(), BLACK);
 
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(5, 0);
  display.print("Temp&Humidity");
  display.drawRect(8, 12, 3, 3, BLACK);
 // display.setCursor(15, 28);
 // display.print("HUMIDITY:");
  display.display();
  */
}
 
// main loop
void loop()
{


    // read humidity
   RH = dht22.getHumidity() * 10;
  // read temperature in degree Celsius
   Temp = dht22.getTemperature() * 10;


  // update temperature and humidity arrays
  if(Temp < 0)
  {
    temperature[0] = '-';
    Temp = abs(Temp);
  }
  else
    temperature[0] = ' ';
  temperature[1] = (Temp / 100) % 10  + '0';
  temperature[2] = (Temp / 10)  % 10  + '0';
  temperature[4] =  Temp % 10 + '0';
 
  if(RH >= 1000)
    humidity[0] = '1';
  else
  humidity[0] = ' ';
  humidity[1]   = (RH / 100) % 10 + '0';
  humidity[2]   = (RH / 10)  % 10 + '0';
  humidity[4]   =  RH % 10 + '0';
 
 //for (int n=0 ; n<50 ;n++)
 //{
 j=analogRead(A0);
 //prev=prev+j ;
 //}
 //j=prev/50 ;


  j=map(j,400,1023,100,0);
 // pres=j;
  if(j>100)
  j=100;
  else if(j<0)
 j=0;
display.clearDisplay(); 
display.setContrast(50);
 if(j<5) 
 {
  // print temperature
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 9);
  display.print("T:");
  display.setTextSize(2);
   display.setCursor(0, 5);
  display.print(temperature);
  // print degree symbol ( ° )
 // display.drawRect(65, 10, 4, 4, BLACK);
   display.drawCircle(67, 3,2, BLACK);
   display.drawCircle(67, 3,1, BLACK);
   display.drawFastHLine(0, 24, display.width(), BLACK);
   display.drawFastHLine(0, 23, display.width(), BLACK);
  // print humidity
  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print("H:");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.print(humidity);
  display.display() ;
  
 }
  else
  {
     // now update the display
display.clearDisplay();
display.setTextSize(2);
   display.setCursor(0,0);
  display.print("Moistur");
  display.drawFastHLine(0, 16, display.width(), BLACK);
  display.setTextSize(3);
 display.setCursor(0,21);
 display.print(j);
  display.print("%");
  display.display();
  delay(1000);
  }
 /*
  display.clearDisplay();   // clear the screen and buffer
  display.display();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Soil Moisture");
  display.setCursor(10,10);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.print("%"); display.println(j);
  display.display();
  delay(2000);
*/
  
 
 
 // delay(1000);  // wait 1 second
  
}

 
