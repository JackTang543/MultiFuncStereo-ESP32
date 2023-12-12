/*  
 * ********************************
 * * MultiFuncStereo 程序部分 v1.1 *
 * ********************************
 *
 * 
 * 
*/



#include <Arduino.h>
#include "sig_btn_driver.h"

#include "sig_app_init.h"
#include "sig_app_callback.h"
#include "sig_app_os.h"
#include "sig_app_menu.h"

#include "sig_VFD1602.h"

#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>

    /// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FM

/// The station that will be tuned by this sketch is 89.30 MHz.
uint16_t main_fm_freq = 9180;

TEA5767 radio;    // Create an instance of Class for Si4703 Chip

uint8_t test1;
byte test2;

void mainsett(){
    radio.setBandFrequency(FIX_BAND, main_fm_freq); 
}


void setup() {
    

    sigApp_InitAllGPIOs();

    radio.init();
    radio.debugEnable();
    radio.setBandFrequency(FIX_BAND, main_fm_freq); // hr3 nearby Frankfurt in Germany
  radio.setVolume(1);
  //radio.setMute(true);
  radio.setMono(false);

    sigApp_InitAllPeph();

    

    sBT401_PowerSet(1);
    delay(200);
    sVFD1602_Init();
    sVFD1602_BrightnessSet(0);
    delay(200);
    sBT401_SendCommand("CR",1);
    
    //MenuShow_MainMusic();

    //sVFD1602_UpdateScreenByCGRAM();
    

    sigOS_Create_AllTask();
    
    delay(2000);
    sVFD1602_BrightnessSet(100);
    
   

    

}

void loop() {

}
