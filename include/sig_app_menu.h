#ifndef __SIG_APP_MENU_H__
#define __SIG_APP_MENU_H__

#include <Arduino.h>

#include "sig_BT401.h"
#include "sig_VFD1602.h"
#include "sig_ina219.h"
#include "sig_tp5100.h"

typedef enum{
    MENU_MAIN_FUNC_MUSIC = 0,
    MENU_MAIN_FUNC_FM = 1
}MENU_MAIN_FUNC_t;

//这里和数据手册的值是一一对应的(除了蓝牙)
typedef enum{
    InstantEventFlag_Null = 0,
    InstantEventFlag_USBIn,
    InstantEventFlag_USBOut,
    InstantEventFlag_TFcardIn,
    InstantEventFlag_TFcardOut,
    InstantEventFlag_BTLink,
    InstantEventFlag_BTNoLink,
    InstantEventFlag_ChangeVol,
    InstantEventFlag_ChangeBrightness,
    InstantEventFlag_ShowBattStatus
}InstantEventFlag_t;



void sigAppMENU(uint8_t page);
void MenuShow_MainMusic();
void sigAppMENU_Handler();

void sigAppMENU_SetPlayedTime(uint16_t _playedtime);
void sigAppMENU_SetPlayAllTime(uint16_t _playalltime);
void sigAppMENU_SetWorkMode(uint8_t _workmode);
void sigAppMENU_SetUsbTfCurrStatus(uint8_t _currstatus);
void sigAppMENU_SetBtCurrStatus(uint8_t _currstatus);
void sigAppMENU_SetInOutInfo(uint8_t _info);
void sigAppMENU_SetVolume(uint8_t _volume);
void sigAppMENU_UpdownVolume(uint8_t updown);
void sigAppMENU_UpdownBrightness(uint8_t updown);

#endif