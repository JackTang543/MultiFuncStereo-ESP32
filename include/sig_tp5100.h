#ifndef __SIG_TP5100_H__
#define __SIG_TP5100_H__

#include <Arduino.h>
#include "define.h"

typedef enum{
    SIG_TP5100_STDBY = 0,
    SIG_TP5100_CHRG
}SIG_TP5100_STATUS_t;


SIG_TP5100_STATUS_t sTP5100_GetStatus();


#endif