#include "sig_app_callback.h"

bool playorstop = 0;



void sig_app_callBack_Btn(uint16_t key_id,sGBD_TRIG_t key_event){
    //TouchCenter
    if(key_id == 3){
        if(key_event == sGBD_TRIG_PRES){
            sBT401_TransComm_Play();
            //Serial.printf("SW%u_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_LPRS){
            //Serial.printf("SW%u_LONG_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_2PRS){
            //Serial.printf("SW%u_DOUBLE_PRESSED\r\n",key_id);
        }
    }//TouchLeft
    else if(key_id == 2){
        if(key_event == sGBD_TRIG_PRES){
            sBT401_TransComm_PrevMusic();
            //Serial.printf("SW%u_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_LPRS){
            //Serial.printf("SW%u_LONG_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_2PRS){
            sigAppMENU_UpdownBrightness(0);
            //Serial.printf("SW%u_DOUBLE_PRESSED\r\n",key_id);
        }
    }//TouchRight
    else if(key_id == 1){
        if(key_event == sGBD_TRIG_PRES){
            sBT401_TransComm_NextMusic();
            //Serial.printf("SW%u_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_LPRS){
            //Serial.printf("SW%u_LONG_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_2PRS){
            sigAppMENU_UpdownBrightness(1);
            //Serial.printf("SW%u_DOUBLE_PRESSED\r\n",key_id);
        }
    }//Encoder1Key
    else if(key_id == 4){
        if(key_event == sGBD_TRIG_PRES){
            playorstop = !playorstop;
            sBT401_TransComm_Play();
            //Serial.printf("SW%u_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_LPRS){
            sBT401_TransComm_NextWorkMode();
            //Serial.printf("SW%u_LONG_PRESSED\r\n",key_id);
        }
        else if(key_event == sGBD_TRIG_2PRS){
            //sBT401_SendCommand("CM",5);
            sBT401_SendCommand("CS",0);
            //Serial.printf("SW%u_DOUBLE_PRESSED\r\n",key_id);
        }
    }

}

uint8_t vol = 10;

uint8_t page = 0;

void sig_app_callBack_EC(uint8_t EC_id,sEC_EV_t EC_event){
    if(EC_id == 1){
        if(EC_event == sEC_EV_UP){
            
            //sigAppMENU_UpdownVolume(1);
        }else if(EC_event == sEC_EV_DOWN){
            
            //sigAppMENU_UpdownVolume(0);
        }
    }
}


