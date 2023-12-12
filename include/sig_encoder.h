#ifndef __SIG_ENCODER_H__
#define __SIG_ENCODER_H__


#include "Arduino.h"

#include "define.h"


//用于保存编码器发生的事件
typedef enum{
    sEC_EV_NULL = 0,    //无事件
    sEC_EV_UP,          //往右转
    sEC_EV_DOWN         //往左转
}sEC_EV_t;

typedef void (*sECTrigCb_t)(uint8_t EC_id,sEC_EV_t EC_event);



void sEC_Init(void);
void sEC_SetECTrigCb(sECTrigCb_t trig_cb);

void sEC_1a_falling(void);
void sEC_1b_falling(void);

void sEC_TrigDetectHandler(void);


#endif
