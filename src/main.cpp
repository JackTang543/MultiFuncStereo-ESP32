/*  
 * ********************************
 * * MultiFuncStereo 程序部分 v1.0 *
 * ********************************
 * 更新日志:
 *  1.0: 初代版本
 * 
 * 
 * ********************************
 * -by SIGHTSEER. 2023.12.12 in HNIP9607
 * 
*/


#include <Arduino.h>

//这是按键驱动
#include "sig_btn_driver.h"
//用于GPIO和外设的初始化
#include "sig_app_init.h"
//管理所有事件的回调函数
#include "sig_app_callback.h"
//用于配置FreeRTOS
#include "sig_app_os.h"
//管理菜单
#include "sig_app_menu.h"

#include "sig_VFD1602.h"





void setup() {
    

    sigApp_InitAllGPIOs();
    sigApp_InitAllPeph();

    

    sBT401_PowerSet(1);
    delay(200);
    sVFD1602_Init();
    sVFD1602_BrightnessSet(0);
    delay(200);
    sBT401_SendCommand("CR",1);
    
    MenuShow_MainMusic();
    

    //sigOS_Create_AllTask();
    
    delay(2000);
    sVFD1602_BrightnessSet(100);
    
    //

    

}

void loop() {
    // Serial.print("Bus Voltage:   "); Serial.print(sINA219_GetBatVolt_mV()); Serial.println(" mV");
    // Serial.print("Shunt Voltage: "); Serial.print(sINA219_GetRshunt_mV()); Serial.println(" mV");
    // Serial.print("Load Voltage:  "); Serial.print(sINA219_GetLoadVolt_mV()); Serial.println(" mV");
    // Serial.print("Current:       "); Serial.print(sINA219_GetCurr_mA()); Serial.println(" mA");
    // Serial.print("Power:         "); Serial.print(sINA219_GetPower_mW()); Serial.println(" mW");
    // Serial.println("");

    
    sVFD1602_CGRAM_WriteNumber(0,0,analogRead(AUDIO_ADC_PIN));
    sVFD1602_UpdateScreenByCGRAM();
    delay(100);
}
