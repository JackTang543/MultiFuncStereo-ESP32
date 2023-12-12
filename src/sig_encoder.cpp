#include "sig_encoder.h"

sECTrigCb_t EC_Trig_Cb;

sEC_EV_t EC1_Flag;


void sEC_Init(){
    EC1_Flag = sEC_EV_NULL;
}

//注册触发回调
void sEC_SetECTrigCb(sECTrigCb_t trig_cb){
    if(trig_cb != NULL){
        EC_Trig_Cb = trig_cb;
    }
}


//下面两个中断函数内只有标志位的设置,减少中断耗时
void sEC_1a_falling(void){
    if(digitalRead(Encoder1bPIN) == LOW){
            if(digitalRead(Encoder1aPIN) == LOW){
                EC1_Flag = sEC_EV_DOWN;
            }
        }
}

void sEC_1b_falling(void){
    if(digitalRead(Encoder1aPIN) == HIGH){
            if(digitalRead(Encoder1bPIN) == HIGH){
                EC1_Flag = sEC_EV_UP;
            }
        }
}

//定时检查触发标志位,调用用户回调
//此函数需要系统定时调用
void sEC_TrigDetectHandler(void){
    if(EC1_Flag == sEC_EV_UP){
        EC1_Flag = sEC_EV_NULL;
        EC_Trig_Cb(1, sEC_EV_UP);
    }else if(EC1_Flag == sEC_EV_DOWN){
        EC1_Flag = sEC_EV_NULL;
        EC_Trig_Cb(1, sEC_EV_DOWN);
    }
}



