#include <Arduino_FreeRTOS.h>

#include <Adafruit_BMP280.h>  //BMP280
Adafruit_BMP280 bmp;

#include "MPU9250.h"    //MPU9250
#include <Wire.h>
MPU9250 IMU(Wire, 0x68);
int status;

void mp( void *pvParameters );
void bmp280( void *pvParameters );

void setup() {
  Serial.begin(9600);
  while (!Serial) {}


  //BMP280
  Serial.println(F("BMP280 test"));

//    if (!bmp.begin(0x76)) {
//      Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
//                       "try a different address!"));
////      while (1) delay(10);
//    }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  //MPU9250
  status = IMU.begin();

//    if (status < 0) {
//      Serial.println("IMU initialization unsuccessful");
//      Serial.println("Check IMU wiring or try cycling power");
//      Serial.print("Status: ");
//      Serial.println(status);
//      while (1) {}
//    }

  xTaskCreate(mp,  "MPU9250",  128,  NULL,  1,  NULL );
  xTaskCreate(bmp280,  "BMP280",  128,  NULL,  2,  NULL );

}

void loop() {}

void mp(void *pvParameters)
{
  (void) pvParameters;

  while (1)
  {
    IMU.readSensor();
    Serial.print(IMU.getAccelX_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelY_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelZ_mss(), 6);
    Serial.print("\t");

    Serial.print(IMU.getGyroX_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroY_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroZ_rads(), 6);
    Serial.print("\t");

    Serial.print(IMU.getMagX_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagY_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagZ_uT(), 6);
    Serial.println();

    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

void bmp280(void *pvParameters)
{
  (void) pvParameters;

  while (1)
  {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature(), 1);
    Serial.println(" *C");
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25), 1);
    Serial.println(" m");
    Serial.println();

    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}
