#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "Arduino.h"

//左右和中间的触摸按键
#define BtnTouchLeftPIN   (12)
#define BtnTouchRightPIN  (8)
#define BtnTouchCenterPIN (13)
//旋转编码器
#define Encoder1aPIN      (10)
#define Encoder1bPIN      (2)
#define Encoder1keyPIN    (6)
//TP5100充电芯片信号输出
#define TP5100StdbyPIN    (18)
#define TP5100ChrgPIN     (19)
//WS2812数据口
#define WS2812_PIN        (11)
//I2C总线:INA219,TEA5767,AT24C02
#define I2CBUS_SCL        (5)
#define I2CBUS_SDA        (4)
//BT401蓝牙模块串口
#define BT401_RX          (1)
#define BT401_TX          (0)
#define BT401_EN          (7)
//VFD1602显示屏TX就是UART0的TX
//ADC
#define AUDIO_ADC_PIN     (3)




#endif 