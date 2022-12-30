#include <Arduino_FreeRTOS.h>
#include "MPU9250.h"
#include <Wire.h>

MPU9250 IMU(Wire, 0x68);
int status;

void mp( void *pvParameters );

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {}
  }
  xTaskCreate(mp,  "BMP280",  128,  NULL,  1,  NULL );

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
