#pragma once
//
//    FILE: CHT8305.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT8305 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CH8305
//


#include "Arduino.h"
#include "Wire.h"


#define CHT8305_LIB_VERSION              (F("0.1.0"))


#define CHT8305_OK                       0
#define CHT8305_ERROR_ADDR               -10
#define CHT8305_ERROR_I2C                -11
#define CHT8305_ERROR_CONNECT            -12

#define CHT8305_ERROR_LASTREAD           -20




class CHT8305
{
public:
  CHT8305(TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  //  address and writeProtectPin is optional
  int      begin(int sda, int scl, const uint8_t address = 0x50);
#endif
  //  address and writeProtectPin is optional
  int      begin(const uint8_t address = 0x50);
  bool     isConnected();

  //  read the temperature and humidity.
  int      read();
  //  lastRead is in MilliSeconds since start sketch
  uint32_t lastRead()                    { return _lastRead; };
  
  //  preferred interface
  float    getHumidity()                 { return _humidity; };
  float    getTemperature()              { return _temperature; };

  //  adding offsets works well in normal range
  // might introduce under- or overflow at the ends of the sensor range
  void     setHumOffset(float offset)    { _humOffset = offset; };
  void     setTempOffset(float offset)   { _tempOffset = offset; };
  float    getHumOffset()                { return _humOffset; };
  float    getTempOffset()               { return _tempOffset; };


  //  todo
  //
  //  setAlarmT() - need to set them both at once.
  //  getAlarmT()
  //  setAlarmH()
  //  getAlarmH()
  //
  //  getConfigRegister() - which flags are most interesting
  //  softreset()


private:
  float    _humOffset     = 0.0;
  float    _tempOffset    = 0.0;
  float    _humidity      = 0.0;
  float    _temperature   = 0.0;
  uint32_t _lastRead      = 0;

  TwoWire* _wire;
  uint8_t  _address       = 0x40;
  
  int _readRegister(uint8_t reg, uint8_t * buf, uint8_t size);
  int _writeRegister(uint8_t reg, uint8_t * buf, uint8_t size);
};


// -- END OF FILE --

