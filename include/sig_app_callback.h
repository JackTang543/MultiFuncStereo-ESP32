#ifndef __SIG_APP_CALLBACK_H__
#define __SIG_APP_CALLBACK_H__
#include "Arduino.h"
#include "sig_btn_driver.h"
#include "sig_encoder.h"
#include "sig_BT401.h"

#include "sig_app_menu.h"

extern uint8_t __ec_status;

void sig_app_callBack_Btn(uint16_t key_id,sGBD_TRIG_t key_event);
void sig_app_callBack_EC(uint8_t EC_id,sEC_EV_t EC_event);


#endif
