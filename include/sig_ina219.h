#ifndef __SIG_INA219_H__
#define __SIG_INA219_H__

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

void sINA219_Init();
float sINA219_GetRshunt_mV();
float sINA219_GetBatVolt_mV();
float sINA219_GetCurr_mA();
float sINA219_GetPower_mW();
float sINA219_GetLoadVolt_mV();

#endif
