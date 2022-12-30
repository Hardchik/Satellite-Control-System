#include <Arduino_FreeRTOS.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;

void bmp280( void *pvParameters );

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  bmp_setup();
  
//  Serial.println(F("BMP280 test"));
//
//  if (!bmp.begin(0x76)) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
//                     "try a different address!"));
//    while (1) delay(10);
//  }
//
//  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
//                  Adafruit_BMP280::SAMPLING_X2,
//                  Adafruit_BMP280::SAMPLING_X16,
//                  Adafruit_BMP280::FILTER_X16,
//                  Adafruit_BMP280::STANDBY_MS_500);
  
  xTaskCreate(bmp280,  "BMP280",  128,  NULL,  1,  NULL );

}

void loop(){}


void bmp280(void *pvParameters)  
{
  (void) pvParameters;


  while (1)
  {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature(),1);
    Serial.println(" *C");
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25),1);
    Serial.println(" m");  
    Serial.println();

    vTaskDelay(250/ portTICK_PERIOD_MS);
  }
}

void bmp_setup(){
  Serial.println(F("BMP280 test"));

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}
