#ifndef __SIG_TEA5767_H__
#define __SIG_TEA5767_H__

#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>

//选择波段76-108MHz
#define SIG_TEA5767_WORLD_BAND RADIO_BAND_FMWORLD
//用于保存频率,格式:9180:91.80MHz
RADIO_FREQ fm_freq = 9170;
//收音机对象
TEA5767 tea;
//收音机信息
RADIO_INFO tea_info;

void sTEA5767_Init();
void sTEA5767_SetFreq(uint16_t freq);
uint8_t sTEA5767_GetRSSI();
uint8_t sTEA5767_GetSNR();
uint16_t sTEA5767_GetFreq();

#endif