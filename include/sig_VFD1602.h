#ifndef __SIG_VFD1602_H__
#define __SIG_VFD1602_H__


#include <Arduino.h>
#include "math.h"
#include "sig_Font.h"

//设置屏幕发送完指令的等待时间
#define DELAY_TIME_MS 1


//清屏
#define DISPCLR  ((uint8_t)0x55)
//屏幕电源控制
#define PWRCTR   ((uint8_t)0xB1)
//设置屏幕亮度
#define DIMMCTR  ((uint8_t)0xA0)
//光标设置闪烁
#define CURCFG   ((uint8_t)0xA1)
//设置光标位置
#define CURPOS   ((uint8_t)0xA2)
//写屏幕上方图标(可连续写)
#define ADRAMWR  ((uint8_t)0xCC)
//写用户显存
#define CGRAMWR  ((uint8_t)0xCD)
//写第0行DCRAM
#define DCRAM0WR ((uint8_t)0xCA)
//写第1行DCRAM
#define DCRAM1WR ((uint8_t)0xCB)

typedef enum{
    PWR_OFF = 0,
    PWR_ON
}sVFD1602_PWR_t;

typedef enum{
    ICON_PLAY = 0,
    ICON_STOP,
    ICON_SDB,
    ICON_TONE,
    ICON_TUNED,
    ICON_AUTO,
    ICON_ST,
    ICON_MONO,
    ICON_TOTAL,
    ICON_RANDOM,
    ICON_CYCLE,
    ICON_1,
    ICON_FLD,
    ICON_ALL,
    ICON_SLEEP,
    ICON_CLOCK,
    ICON_POINT
}sVFD1602_Icon_t;

typedef enum{
    ICON_EN_OFF,
    ICON_EN_ON
}sVFD1602_Icon_EN_t;

typedef struct{
    sVFD1602_Icon_t icon;
    sVFD1602_Icon_EN_t en;
    uint8_t Data_A;
    uint8_t Data_D;
}sVFD1602_ICON_Table_t;

extern sCGRAM_Char_t SymbolFont[];
extern sCGRAM_Char_t CharFont[];

//这些是用户写GRAM的函数
void sVFD1602_GRAM_BrightnessSet(uint8_t bright_percent);
void sVFD1602_GRAM_IconSet(sVFD1602_Icon_t icon,sVFD1602_Icon_EN_t en);
void sVFD1602_GRAM_Clear(void);
void sVFD1602_GRAM_WriteString(uint8_t x,uint8_t y,char* str);


void sVFD1602_ClearDisplay(void);
void sVFD1602_PowerSet(sVFD1602_PWR_t en);
void sVFD1602_BrightnessSet(uint8_t bright_percent);
void sVFD1602_CursorENandBlinkSet(uint8_t blink);
void sVFD1602_CursorSet(uint8_t x,uint8_t y);
void sVFD1602_Init();
void sVFD1602_UpdateScreenByGRAM(void);
void sVFD1602_GRAM_WriteCGRAM(void);

void sVFD1602_UpdateScreenByCGRAM(void);
void sVFD1602_CGRAM_WriteUserChar(uint8_t x,uint8_t y,sCGRAM_Char_t user_char);
void sVFD1602_CGRAM_WriteNumber(uint8_t x,uint8_t y,uint16_t num);
void sVFD1602_CGRAM_WriteString(uint8_t x,uint8_t y,char* str,uint8_t reverse);
void sVFD1602_CGRAM_WriteChar(uint8_t x,uint8_t y,char c);
void sVFD1602_CGRAM_Clear(void);

#endif
