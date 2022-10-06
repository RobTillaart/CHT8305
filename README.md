[![Arduino CI](https://github.com/RobTillaart/CHT8305/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8305/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8305/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8305.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8305/releases)

# CHT8305

Arduino library for CHT8305 temperature and humidity sensor.

**EXPERIMENTAL** not tested yet - todo buy hardware + test.


## Description

The CHT8305 is a temperature and humidity sensor.

It supports an ALERT pin, see below.


### Hardware


TODO  NOT CORRECT CHECK DATASHEET.
Placeholder.

```
//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8305  |   TODO CHECK DATASHEET.
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |   ? depends on address to select
//          |               |
//  IRQ ----| ALERT         |   only if enabled.
//          +---------------+
```


### Alert

It has ALERT logic output pin with open drain structure, which is active low.
(if your breakout supports this)


## I2C 

I2C bus speeds supported up to 400 KHz.

|  AD0  |   Address  |
|:-----:|:----------:|
|  GND  |    0x40    |
|  VCC  |    0x41    |
|  SDA  |    0x42    |
|  SCL  |    0x43    |


Pull ups are needed on SDA, SCL and optional to ALERT.



## Interface

- **CHT8305(TwoWire \*wire = &Wire)** Constructor with default I2C bus.
- **int begin(const uint8_t address = 0x40)** sets address, deault = 0x40.
- **int begin(int sda, int scl, const uint8_t address = 0x40)** idem ESP32 et. al.
- **bool isConnected()** checks if address can be seen onthe I2C bus.
- **int read()** reads the temperature and humidity.
- **uint32_t lastRead()** returns lastRead is in MilliSeconds since start sketch.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** is called again.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** is called again.

  
### Offset

Adding offsets works well in normal range but might introduce 
under- or overflow at the ends of the sensor range.
  
- **void setHumOffset(float offset)** idem.
- **void setTempOffset(float offset)** idem.
- **float getHumOffset()** idem.
- **float getTempOffset()** idem.


### Config register 

- **void setConfigRegister(uint16_t bitmask)**
- **uint16_t getConfigRegister()**
- **void softReset()**


- TODO more specific functions.

|  bit  |  meaning        |
|:-----:|:----------------|
|  15   |  soft reset     |
|  14   |  clock stretch  |
|  13   |  heater         |
|  12   |  mode           |
|  11   |  vccs           |
|  10   |  T-RES          |
|  9-8  |  H-res          |
|  7-6  |  ALTM           |
|  5    |  APS            |
|  4    |  HALT           |
|  3    |  TALT           |
|  2    |  VCCenable      |
|  1-0  |  reserved.      |


### Alert

TODO elaborate


### Voltage

TODO elaborate

- **float getVoltage()**


### Meta data

TODO elaborate

- **uint16_t getManufacturer()** 
- **uint16_t getVersionID()**


## Future

- improve documentation
- make code functional complete
- fix TODO's in code


#### test

- buy hardware 
- test AVR, ESP32, ...
- test performance
= test I2C speed

