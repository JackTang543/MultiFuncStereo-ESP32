#ifndef __SIG_APP_INIT_H__
#define __SIG_APP_INIT_H__

#include "Arduino.h"
#include "sig_btn_driver.h"
#include "sig_encoder.h"
#include "sig_ina219.h"
#include "sig_app_callback.h"
#include "define.h"




void sigApp_InitAllGPIOs(void);
void sigApp_InitAllPeph(void);

void sigInit_BtnHandler(void);


#endif