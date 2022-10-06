//
//    FILE: CHT8305_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8305 I2C humidity & temperature sensor
//

//  Always check datasheet - front view
//
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2   CHT8305  |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+


#include "CHT8305.h"

CHT8305 CHT;

uint8_t count = 0;

void setup()
{
  CHT.begin(0x40);   //  default address

  Wire.setClock(400000);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8305_LIB_VERSION: ");
  Serial.println(CHT8305_LIB_VERSION);
  Serial.println();

  delay(1000);
}


void loop()
{
  if (millis() - CHT.lastRead() >= 1000)
  {
    // READ DATA
    uint32_t start = micros();
    int status = CHT.read();
    uint32_t stop = micros();

    if ((count % 10) == 0)
    {
      count = 0;
      Serial.println();
      Serial.println("Type\tHumidity (%)\tTemp (°C)\tTime (µs)\tStatus");
    }
    count++;

    Serial.print("CHT8305\t");
    // DISPLAY DATA, sensor has only one decimal.
    Serial.print(CHT.getHumidity(), 1);
    Serial.print("\t\t");
    Serial.print(CHT.getTemperature(), 1);
    Serial.print("\t\t");
    Serial.print(stop - start);
    Serial.print("\t\t");
    switch (status)
    {
      case CHT8305_OK:
        Serial.print("OK");
        break;
      case CHT8305_ERROR_ADDR:
        Serial.print("Address error");
        break;
      case CHT8305_ERROR_I2C:
        Serial.print("I2C error");
        break;
      case CHT8305_ERROR_CONNECT:
        Serial.print("Connect error");
        break;
      case CHT8305_ERROR_LASTREAD:
        Serial.print("Last read error");
        break;
      default:
        Serial.print("Unknown error");
        break;
    }
    Serial.print("\n");
  }
}


// -- END OF FILE --
